// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Weapon.generated.h"


class AFleetCommGameMode;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLEETCOMM_API UWeapon : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeapon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool DualWeapon;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USkeletalMeshComponent* PrimarySkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* BulletSpawnPoint;
protected:
	UFUNCTION()
	virtual void GetBullet();

	UPROPERTY()
	AFleetCommGameMode* GameMode;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	virtual bool FireWeapon();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxAmmo;

	UPROPERTY()
	float CurrentAmmo = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float FireRate = 1.0f;

	bool ReadyToFire = true;
		
};
