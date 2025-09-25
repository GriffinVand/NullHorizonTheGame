// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShipMovementComponent.h"
#include "ShipFreeRotationMovement.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FLEETCOMM_API UShipFreeRotationMovement : public UShipMovementComponent
{
	GENERATED_BODY()

public:
	// virtual void MovementUpdate(float DeltaTime, TObjectPtr<UPrimitiveComponent> UpdatedComponent) override;
	// virtual void PitchRoll(const FInputActionValue& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent) override;
	// virtual void Yaw(const FInputActionValue& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent) override;
	virtual void OnActivation(UShipMovementComponent* PreviousMovement, TObjectPtr<UPrimitiveComponent> UpdatedComponent) override;
	virtual void AccelerateByInput(const FInputActionValue& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent) override;
	virtual void DecelerateByInput(const FInputActionValue& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent) override;
	
};
