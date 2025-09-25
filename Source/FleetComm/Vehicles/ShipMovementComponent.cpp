// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UShipMovementComponent::UShipMovementComponent()
{
	//PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UShipMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// if (UpdatedComponent == nullptr)
	// {
	// 	UpdatedComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	// }
}

void UShipMovementComponent::OnActivation(UShipMovementComponent* PreviousMovement, TObjectPtr<UPrimitiveComponent> UpdatedComponent)
{
	if (!PreviousMovement) return;

	CurrentDirAcceleration = PreviousMovement->CurrentDirAcceleration;

	CurrentRotAcceleration = PreviousMovement->CurrentRotAcceleration;
	CurrentYawAcceleration = PreviousMovement->CurrentYawAcceleration;

	UpdatedComponent->SetLinearDamping(DampingFactor);
	UpdatedComponent->SetAngularDamping(RotDampingFactor);
}

void UShipMovementComponent::OnDeactivation(UShipMovementComponent* PreviousMovement, TObjectPtr<UPrimitiveComponent> UpdatedComponent)
{
	
}


void UShipMovementComponent::MovementUpdate(float DeltaTime, TObjectPtr<UPrimitiveComponent> UpdatedComponent)
{
	if (UpdatedComponent->GetPhysicsLinearVelocity().Length() < MaxSpeed) UpdatedComponent->AddForce(CurrentDirAcceleration * DeltaTime);
	if (UpdatedComponent->GetPhysicsAngularVelocityInRadians().Length() < MaxRollSpeed) UpdatedComponent->AddTorqueInRadians((CurrentRotAcceleration + CurrentYawAcceleration) * DeltaTime, NAME_None, true);
}

void UShipMovementComponent::PitchRollByInput(const FInputActionValue& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent)
{
	PitchRollByValue(Value.Get<FVector2D>(), UpdatedComponent);
}
void UShipMovementComponent::PitchRollByValue(const FVector2D& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent)
{
	FVector LocalTorque(Value.X, Value.Y, 0.0f);
	LocalTorque *= RollSpeed;
	FVector WorldTorque = UpdatedComponent->GetComponentTransform().TransformVectorNoScale(LocalTorque);
	CurrentRotAcceleration = WorldTorque;
}

void UShipMovementComponent::YawByInput(const FInputActionValue& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent)
{
	YawByValue(Value.Get<float>(), UpdatedComponent);
}
void UShipMovementComponent::YawByValue(const float& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent)
{
	FVector LocalTorque = FVector(0, 0, Value);
	LocalTorque *= YawSpeed;
	FVector WorldTorque = UpdatedComponent->GetComponentTransform().TransformVectorNoScale(LocalTorque);
	CurrentYawAcceleration = WorldTorque;
}

void UShipMovementComponent::AccelerateByInput(const FInputActionValue& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent)
{
	AccelerateByValue(Value.Get<float>(), UpdatedComponent);
}
void UShipMovementComponent::AccelerateByValue(const float& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent)
{
	CurrentDirAcceleration = UpdatedComponent->GetForwardVector() * Value * AccelSpeed;
}


void UShipMovementComponent::DecelerateByInput(const FInputActionValue& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent)
{
	DecelerateByValue(Value.Get<float>(), UpdatedComponent);
	if (!CurrentDirAcceleration.IsNearlyZero())
		CurrentDirAcceleration -= CurrentDirAcceleration.GetSafeNormal() * Value.Get<float>() * BrakeSpeed;
}
void UShipMovementComponent::DecelerateByValue(const float& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent)
{
	if (!CurrentDirAcceleration.IsNearlyZero())
		CurrentDirAcceleration -= CurrentDirAcceleration.GetSafeNormal() * Value * BrakeSpeed;
}

void UShipMovementComponent::AIRotate(FVector Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent)
{
	// Main difference is that Value IS a world vector and does not need to convert values
	Value *= RollSpeed;
	
	FVector PitchRoll(Value.X, Value.Y, 0.0f);
	FVector Yaw(0.0f, 0.0f, Value.Z);
	
	CurrentRotAcceleration = PitchRoll;
	CurrentYawAcceleration = Yaw;
}
