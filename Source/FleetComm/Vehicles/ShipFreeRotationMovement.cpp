// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipFreeRotationMovement.h"

// void UShipFreeRotationMovement::MovementUpdate(float DeltaTime, TObjectPtr<UPrimitiveComponent> UpdatedComponent)
// {
// 	if (UpdatedComponent->GetPhysicsLinearVelocity().Length() < MaxSpeed) UpdatedComponent->AddForce(CurrentDirAcceleration * DeltaTime);
// 	if (UpdatedComponent->GetPhysicsAngularVelocityInRadians().Length() < MaxRollSpeed) UpdatedComponent->AddTorqueInRadians((CurrentRotAcceleration + CurrentYawAcceleration) * DeltaTime);
// }
//
// void UShipFreeRotationMovement::Yaw(const FInputActionValue& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent)
// {
// 	Super::Yaw(Value, UpdatedComponent);
// }
//
// void UShipFreeRotationMovement::PitchRoll(const FInputActionValue& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent)
// {
// 	Super::PitchRoll(Value, UpdatedComponent);
// }

void UShipFreeRotationMovement::OnActivation(UShipMovementComponent* PreviousMovement, TObjectPtr<UPrimitiveComponent> UpdatedComponent)
{
	if (!PreviousMovement) return;

	UpdatedComponent->SetLinearDamping(DampingFactor);
	UpdatedComponent->SetAngularDamping(RotDampingFactor);
}

void UShipFreeRotationMovement::AccelerateByInput(const FInputActionValue& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent)
{
	
}

void UShipFreeRotationMovement::DecelerateByInput(const FInputActionValue& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent)
{
	
}
