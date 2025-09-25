// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShipMovementComponent.generated.h"


struct FInputActionValue;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLEETCOMM_API UShipMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShipMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Movement, meta=(AllowPrivateAccess = "true"))
	float MaxSpeed = 3000.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Movement, meta=(AllowPrivateAccess = "true"))
	float AccelSpeed = 100.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Movement, meta=(AllowPrivateAccess = "true"))
	float BrakeSpeed = 300.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Movement, meta=(AllowPrivateAccess = "true"))
	float DampingFactor = 0.99f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Movement, meta=(AllowPrivateAccess = "true"))
	float MaxRollSpeed = 2000.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Movement, meta=(AllowPrivateAccess = "true"))
	float RollSpeed = 60.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Movement, meta=(AllowPrivateAccess = "true"))
	float YawSpeed = 30.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Movement, meta=(AllowPrivateAccess = "true"))
	float RotDampingFactor = 0.99f;

	//FVector CurrentDirVelocity;
	FVector CurrentDirAcceleration;

	//FVector CurrentRotVelocity;
	FVector CurrentRotAcceleration;
	FVector CurrentYawAcceleration;

	virtual void OnActivation(UShipMovementComponent* PreviousMovement, TObjectPtr<UPrimitiveComponent> UpdatedComponent);
	virtual void OnDeactivation(UShipMovementComponent* PreviousMovement, TObjectPtr<UPrimitiveComponent> UpdatedComponent);

	virtual void MovementUpdate(float DeltaTime, TObjectPtr<UPrimitiveComponent> UpdatedComponent);

	virtual void PitchRollByInput(const FInputActionValue& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent);
	virtual void PitchRollByValue(const FVector2D& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent);
	virtual void YawByInput(const FInputActionValue& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent);
	virtual void YawByValue(const float& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent);
	virtual void AccelerateByInput(const FInputActionValue& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent);
	virtual void AccelerateByValue(const float& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent);
	virtual void DecelerateByInput(const FInputActionValue& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent);
	virtual void DecelerateByValue(const float& Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent);
	virtual void AIRotate(FVector Value, TObjectPtr<UPrimitiveComponent> UpdatedComponent);
		
};
