#pragma once
#include "CoreMinimal.h"
#include "WeaponDefinition.h"
#include "WeaponFireTypeData.generated.h"

class UWeaponFireType;

UCLASS(BlueprintType)
class FLEETCOMM_API UWeaponFireTypeData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWeaponFireType> FireTypeClass;
};

UCLASS(BlueprintType)
class FLEETCOMM_API UProjectileFireTypeData : public UWeaponFireTypeData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ProjectileCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FVector> ProjectileOffsets;
};

UCLASS(BlueprintType)
class FLEETCOMM_API UHitScanFireTypeData : public UWeaponFireTypeData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 HitScanCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FVector> HitScanOffsets;
};

UCLASS(BlueprintType)
class FLEETCOMM_API UBeamFireTypeData : public UWeaponFireTypeData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 BeamCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BeamWidth;
};
