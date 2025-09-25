#pragma once
#include "CoreMinimal.h"
#include "WeaponFireBehaviorData.generated.h"

class UWeaponFireBehavior;

UCLASS(BlueprintType)
class FLEETCOMM_API UWeaponFireBehaviorData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	bool Automatic;
	UPROPERTY(EditAnywhere)
	float FireRate;
	UPROPERTY(EditAnywhere)
	float CooldownRate;
	UPROPERTY(EditAnywhere)
	float OverheatRate;
	UPROPERTY(EditAnywhere)
	float OverheatDelay;
	UPROPERTY(EditAnywhere)
	int32 MaxAmmo;
	UPROPERTY(EditAnywhere)
	int32 AmmoCost;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWeaponFireBehavior> FireBehaviorClass;
	
};

UCLASS(BlueprintType)
class FLEETCOMM_API UDefaultFireBehaviorData : public UWeaponFireBehaviorData
{
	GENERATED_BODY()
public:
	
};

UCLASS(BlueprintType)
class FLEETCOMM_API ULockOnFireBehaviorData : public UWeaponFireBehaviorData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float LockRate;
	UPROPERTY(EditAnywhere)
	int32 ShotsPerLock;
};

UCLASS(BlueprintType)
class FLEETCOMM_API UChargeUpBehaviorData : public UWeaponFireBehaviorData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float ChargeRate;
	UPROPERTY(EditAnywhere)
	float ChargeDecayRate;
	UPROPERTY(EditAnywhere)
	float ChargeLostPerShot;
};
