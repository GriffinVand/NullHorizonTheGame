#pragma once
#include "CoreMinimal.h"
#include "FleetComm/Weapons/PoolableActor.h"
#include "WeaponDefinition.generated.h"

class UWeaponFireModifierData;
class UWeaponFireBehaviorData;
class UWeaponFireTypeData;
class ATestDummy;
class UWeaponBaseUI;


UENUM(BlueprintType)
enum class EFireState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Firing UMETA(DisplayName = "Firing"),
	StartFire UMETA(DisplayName = "StartFire"),
	StopFire UMETA(DisplayName = "StopFire"),
};

UENUM(BlueprintType)
enum class EFireType : uint8
{
	Projectile UMETA(DisplayName = "Projectile"),
	Hitscan UMETA(DisplayName = "Hitscan"),
	Beam UMETA(DisplayName = "Beam"),
};

USTRUCT(BlueprintType)
struct FFireOutput
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EFireState FireState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Origin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator Direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATestDummy* TargetActor = nullptr;
};

UCLASS(BlueprintType)
class FLEETCOMM_API UWeaponDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWeaponFireBehaviorData* WeaponFireBehaviorData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWeaponFireTypeData* WeaponFireTypeData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UWeaponBaseUI> WeaponUIClass;
};
