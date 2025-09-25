#pragma once
#include "CoreMinimal.h"
#include "WeaponFireBehaviorData.generated.h"

UCLASS(BlueprintType)
class FLEETCOMM_API UWeaponFireBehaviorData : public UDataAsset
{
	GENERATED_BODY()
public:
	
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
	
};

UCLASS(BlueprintType)
class FLEETCOMM_API UChargeUpBehaviorData : public UWeaponFireBehaviorData
{
	GENERATED_BODY()
public:
};
