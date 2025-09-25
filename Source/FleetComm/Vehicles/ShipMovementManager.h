// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShipMovementComponent.h"
#include "Components/ActorComponent.h"
#include "ShipMovementManager.generated.h"


struct FInputActionValue;
class UShipMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLEETCOMM_API UShipMovementManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	
	UShipMovementManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()//EditDefaultsOnly, BlueprintReadOnly, Instanced, Category = "Movement")
	TArray<UShipMovementComponent*> ShipMovementComponents;
	UPROPERTY()
	UShipMovementComponent* CurrentMovementComponent = nullptr;
private:
	int32 CurrentMovementCompIndex = 0;

public:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UPrimitiveComponent> UpdatedComponent = nullptr;
	
	UFUNCTION()
	void ToggleFlightMode();
	
	UFUNCTION(BlueprintCallable)
	UShipMovementComponent* GetCurrentMovementComponent() {return CurrentMovementComponent;}

	UFUNCTION(BlueprintCallable)
	bool IsCurrentAngularVelocityGreaterThanMaxSpeedPercent(float Percent)
	{
		if (CurrentMovementComponent == nullptr || UpdatedComponent == nullptr) return false;
		return ((UpdatedComponent->GetPhysicsAngularVelocityInRadians().Length() / CurrentMovementComponent->MaxRollSpeed) > (Percent));
	}
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void MovementUpdate(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	virtual void PitchRoll(const FVector2D& Value);
	virtual void PitchRollByInput(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	virtual void Yaw(const float& Value);
	virtual void YawByInput(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	virtual void Accelerate(const float& Value);
	virtual void AccelerateByInput(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	virtual void Decelerate(const float& Value);
	virtual void DecelerateByInput(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	virtual void AIRotate(FVector Value);
};
