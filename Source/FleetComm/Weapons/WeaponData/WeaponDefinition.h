#pragma once
#include "CoreMinimal.h"
#include "FleetComm/Weapons/PoolableActor.h"
#include "WeaponDefinition.generated.h"

class UWeaponFireModifierData;
class UWeaponFireBehaviorData;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFireType FireType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Origin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ProjectileCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APoolableActor> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BeamDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* TargetActor = nullptr;
};

UCLASS(BlueprintType)
class FLEETCOMM_API UWeaponDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWeaponFireBehaviorData* WeaponFireBehaviorDataAsset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> ProjectileSubClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMesh* WeaponMesh;
	
	
};
