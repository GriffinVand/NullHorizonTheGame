#pragma once
#include "CoreMinimal.h"
#include "FleetComm/Weapons/Weapon.h"
#include "FleetComm/Weapons/WeaponData/WeaponFireTypeData.h"
#include "WeaponFireType.generated.h"

class UWeaponComponent;

UCLASS()
class FLEETCOMM_API UWeaponFireType : public UObject
{
	GENERATED_BODY()
public:

	bool bReady = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EFireType FireType;
	
	virtual void HandleFireOutput(UWeaponComponent* Owner, const FFireOutput& FireOutput);
	virtual void HandleFire(UWeaponComponent* Owner, const FFireOutput& FireOutput) {}
	virtual void HandleFireStart(UWeaponComponent* Owner, const FFireOutput& FireOutput) { HandleFire(Owner, FireOutput); }
	virtual void HandleFireStop(UWeaponComponent* Owner, const FFireOutput& FireOutput) {}

	virtual void InitializeFireType(UWeaponFireTypeData* FireTypeData);
	
};

UCLASS()
class FLEETCOMM_API UProjectileFireType : public UWeaponFireType
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ProjectileCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FVector> ProjectileSpread;
	
	virtual void HandleFire(UWeaponComponent* Owner, const FFireOutput& FireOutput) override;
	virtual void InitializeFireType(UWeaponFireTypeData* FireTypeData) override;
	
};

UCLASS()
class FLEETCOMM_API UHitScanFireType : public UWeaponFireType
{
	GENERATED_BODY()
	public:
	
};

UCLASS()
class FLEETCOMM_API UBeamFireType : public UWeaponFireType
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 BeamCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BeamWidth;

	virtual void HandleFireStart(UWeaponComponent* Owner, const FFireOutput& FireOutput) override;
	virtual void HandleFireStop(UWeaponComponent* Owner, const FFireOutput& FireOutput) override;
	virtual void HandleFire(UWeaponComponent* Owner, const FFireOutput& FireOutput) override;
	
};


