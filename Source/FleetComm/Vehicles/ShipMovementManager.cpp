// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipMovementManager.h"

#include "ShipMovementComponent.h"

// Sets default values for this component's properties
UShipMovementManager::UShipMovementManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UShipMovementManager::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->GetComponents<UShipMovementComponent>(ShipMovementComponents);
	if (ShipMovementComponents.Num() > 0) CurrentMovementComponent = ShipMovementComponents[0];
	
	if (UpdatedComponent == nullptr)
	{
		UpdatedComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	}
}

// Called every frame
void UShipMovementManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MovementUpdate(DeltaTime);
}

void UShipMovementManager::ToggleFlightMode()
{
	CurrentMovementCompIndex++;
	if (CurrentMovementCompIndex >= ShipMovementComponents.Num())
		CurrentMovementCompIndex = 0;
	if (UShipMovementComponent* NewComp = ShipMovementComponents[CurrentMovementCompIndex])
	{
		NewComp->OnActivation(CurrentMovementComponent, UpdatedComponent);
		CurrentMovementComponent = NewComp;
	}
}

void UShipMovementManager::MovementUpdate(float DeltaTime)
{
	if (CurrentMovementComponent) CurrentMovementComponent->MovementUpdate(DeltaTime, UpdatedComponent);
}

void UShipMovementManager::YawByInput(const FInputActionValue& Value)
{
	if (CurrentMovementComponent) CurrentMovementComponent->YawByInput(Value, UpdatedComponent);
}
void UShipMovementManager::Yaw(const float& Value)
{
	if (CurrentMovementComponent) CurrentMovementComponent->YawByValue(Value, UpdatedComponent);
}

void UShipMovementManager::PitchRollByInput(const FInputActionValue& Value)
{
	if (CurrentMovementComponent) CurrentMovementComponent->PitchRollByInput(Value, UpdatedComponent);
}
void UShipMovementManager::PitchRoll(const FVector2D& Value)
{
	if (CurrentMovementComponent) CurrentMovementComponent->PitchRollByValue(Value, UpdatedComponent);
}

void UShipMovementManager::AccelerateByInput(const FInputActionValue& Value)
{
	if (CurrentMovementComponent)
	{
		CurrentMovementComponent->AccelerateByInput(Value, UpdatedComponent);
	}
}
void UShipMovementManager::Accelerate(const float& Value)
{
	if (CurrentMovementComponent)
	{
		CurrentMovementComponent->AccelerateByValue(Value, UpdatedComponent);
	}
}

void UShipMovementManager::DecelerateByInput(const FInputActionValue& Value)
{
	if (CurrentMovementComponent) CurrentMovementComponent->DecelerateByInput(Value, UpdatedComponent);
}
void UShipMovementManager::Decelerate(const float& Value)
{
	if (CurrentMovementComponent) CurrentMovementComponent->DecelerateByValue(Value, UpdatedComponent);
}

void UShipMovementManager::AIRotate(FVector Value)
{
	if (CurrentMovementComponent)
	{
		CurrentMovementComponent->AIRotate(Value, UpdatedComponent);
	}
}
