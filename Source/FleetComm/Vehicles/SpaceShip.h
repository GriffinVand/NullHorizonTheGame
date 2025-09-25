// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "FleetComm/Weapons/WeaponFramework/WeaponComponent.h"
#include "GameFramework/Pawn.h"
#include "SpaceShip.generated.h"

class UShipMovementManager;
class UShipMovementComponent;
struct FEnhancedInputActionEventBinding;
class UWeapon;
class USpringArmComponent;
struct FInputActionValue;
class UFloatingPawnMovement;
class UInputAction;
class UInputMappingContext;

UCLASS()
class FLEETCOMM_API ASpaceShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpaceShip();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString ShipName = "TempName";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString ShipInfo = "TempInfo";
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleCollider;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ShipMesh;

	UFUNCTION()
	virtual void ToggleShipMenu();
	UFUNCTION()
	virtual void OpenMenu();
	UFUNCTION()
	virtual void CloseMenu();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> ShipMenuClass = nullptr;

	UPROPERTY()
	UUserWidget* ShipMenuWidget = nullptr;
	
#pragma region Inputs/Controls
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* PrimaryFireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SecondaryFireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* PitchRollAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* YawAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* AccelAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* DecelAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ToggleFlightMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ResetCamAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ToggleShipMenuAction;
	
	TMap<UInputAction*, FEnhancedInputActionEventBinding*> InputBindings;
	
	virtual void PossesShip(APlayerController*);
	virtual void UnpossesShip();
	
#pragma endregion Inputs/Controls

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Movement)
	UShipMovementManager* ShipMovementManager;

#pragma region Weapons
	
	virtual void PrimaryFire(const FInputActionValue& Value);
	virtual void SecondaryFire(const FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UWeapon* PrimaryWeapon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UWeapon* SecondaryWeapon; 

	virtual void PrimaryFireStarted(const FInputActionValue& Value);
	virtual void PrimaryFireEnded(const FInputActionValue& Value);
	virtual void SecondaryFireStarted(const FInputActionValue& Value);
	virtual void SecondaryFireEnded(const FInputActionValue& Value);

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponSlot ActiveSlot = EWeaponSlot::Primary;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponComponent* PrimaryWeaponComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponComponent* SecondaryWeaponComponent;
	
	
	
#pragma endregion Weapons
	
#pragma region Camera
	
	virtual void Look(const FInputActionValue& Value);
	virtual void ResetCam(const FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* CameraArm;

#pragma endregion Camera
	
};
