#pragma once
#include "CoreMinimal.h"
#include "TargetFinderComponent.h"
#include "FleetComm/Weapons/WeaponData/WeaponDefinition.h"
#include "WeaponFireBehavior.generated.h"

class APoolableActor;
class UWeaponComponent;

USTRUCT(BlueprintType)
struct FDefaultUIOutput
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentFireDelay = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAmmo = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAmmo = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHeatLevel = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OverheatRate = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentOverheatTime = 0.f;
};

USTRUCT(BlueprintType)
struct FChargeUpUIOutput : public FDefaultUIOutput
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentChargeLevel = 0.f;
	
};

USTRUCT(BlueprintType)
struct FLockOnUIOutput : public FDefaultUIOutput
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentLockProgress = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* TargetActor = nullptr;
};

UCLASS()
class FLEETCOMM_API UWeaponFireBehavior : public UObject
{
	GENERATED_BODY()
public:

	bool bReady = false;
	
	bool bFiring = false;
	bool bFireHeld = false;
	bool bStopFire = false;
	bool bStartFire = false;
	
	bool Automatic = true;
	int32 MaxAmmo = 0;
	int32 CurrentAmmo = 50;
	int32 AmmoCost = 1;
	
	bool Overheated = false;

	float FireRate = 10.f;
	float CurrentFireDelay = 0.f;
	
	float CooldownRate = 0.1f;
	float CurrentHeatLevel = 0.f;

	float OverheatRate = 0.1f;
	float OverheatRepairTime = 2.f;
	float CurrentOverheatTime = 0.f;
	
	virtual void FirePressed(UWeaponComponent* Owner);
	virtual void FireReleased(UWeaponComponent* Owner);
	virtual FFireOutput UpdateBehavior(float DeltaTime, UWeaponComponent* Owner);
	virtual void UpdateHeatCooldown(float DeltaTime);
	virtual void UpdateFireCooldown(float DeltaTime);
	virtual bool CanFire();
	virtual void OnFire();
	virtual void ApplyHeat();
	virtual void InitializeBehavior(UWeaponFireBehaviorData* BehaviorData, UWeaponComponent* Owner);
	virtual TSharedPtr<FDefaultUIOutput> GetUIOutput();
	void FillDefaultUIOutput(FDefaultUIOutput& UIOutput);
};

UCLASS()
class FLEETCOMM_API UDefaultFireBehavior : public UWeaponFireBehavior
{
	GENERATED_BODY()

public:
	
};

UCLASS()
class FLEETCOMM_API UChargeUpFireBehavior : public UWeaponFireBehavior
{
	GENERATED_BODY()
public:

	float ChargeRate = 0.5f;
	float ChargeDecayRate = 0.1f;
	float CurrentChargeLevel = 0.f;
	float ChargeLostPerShot = 1.f;

	virtual void InitializeBehavior(UWeaponFireBehaviorData* BehaviorData, UWeaponComponent* Owner) override;
	virtual FFireOutput UpdateBehavior(float DeltaTime, UWeaponComponent* Owner) override;
	virtual void OnFire() override;
	void ApplyChargeCost();
	virtual bool CanFire() override;
	void UpdateChargeLevel(float DeltaTime);
	virtual TSharedPtr<FDefaultUIOutput> GetUIOutput() override;
};

UCLASS()
class FLEETCOMM_API ULockOnFireBehavior : public UWeaponFireBehavior
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
	ATestDummy* TargetDummy = nullptr;
	UPROPERTY(EditAnywhere)
	UTargetFinderComponent* TargetFinderComp;

	float LockRate = 0.5;
	float CurrentLockProgress = 0.f;
	int32 ShotsPerLock = 1;
	bool bLocking = true;
	
	virtual void FirePressed(UWeaponComponent* Owner) override;
	virtual void FireReleased(UWeaponComponent* Owner) override;
	virtual void InitializeBehavior(UWeaponFireBehaviorData* BehaviorData, UWeaponComponent* Owner) override;
	virtual FFireOutput UpdateBehavior(float DeltaTime, UWeaponComponent* Owner) override;
	virtual void OnFire() override;
	virtual bool CanFire() override;
	void TryStartLock(UWeaponComponent* Owner);
	void UpdateLockProgress(float DeltaTime);
	virtual TSharedPtr<FDefaultUIOutput> GetUIOutput() override;
	
};
