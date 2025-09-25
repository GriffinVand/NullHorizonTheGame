#pragma once
#include "CoreMinimal.h"
#include "FleetComm/Weapons/WeaponData/WeaponDefinition.h"
#include "WeaponFireBehavior.generated.h"

class APoolableActor;
class UWeaponComponent;


UCLASS()
class FLEETCOMM_API UWeaponFireBehavior : public UObject
{
	GENERATED_BODY()
public:
	bool Automatic = true;
	
	bool Firing = false;
	bool Overheated = false;

	float FireRate = 10.f;
	float CurrentFireDelay = 0.f;
	
	float CooldownRate = 0.1f;
	float CurrentCooldownLevel = 0.f;

	float OverheatRate = 0.01f;
	float OverheatDelay = 2.f;
	float CurrentOverheatTime = 0.f;
	
	virtual void FirePressed(UWeaponComponent* Owner) {}
	virtual void FireReleased(UWeaponComponent* Owner) {}
	virtual void UpdateBehavior(float DeltaTime) {}
	virtual void UpdateHeatCooldown(float DeltaTime);
	virtual void UpdateFireCooldown(float DeltaTime);
	virtual bool CanFire();
	virtual FFireOutput TryFire(UWeaponComponent* Owner) { return FFireOutput(); }
	virtual void OnFired() {}
};

UCLASS()
class FLEETCOMM_API UDefaultFireBehavior : public UWeaponFireBehavior
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<APoolableActor> ProjectileSubclass;

	virtual void FirePressed(UWeaponComponent* Owner) override;
	virtual void FireReleased(UWeaponComponent* Owner) override;
	virtual void UpdateBehavior(float DeltaTime) override;
	virtual FFireOutput TryFire(UWeaponComponent* Owner) override;
};

UCLASS()
class FLEETCOMM_API UChargeUpFireBehavior : public UWeaponFireBehavior
{
	GENERATED_BODY()
public:

	float ChargeRate = 0.5f;
	float CurrentChargeLevel = 0.f;
};

UCLASS()
class FLEETCOMM_API ULockOnFireBehavior : public UWeaponFireBehavior
{
	GENERATED_BODY()
public:

	bool HasTarget = false;
	float MaxLockProgress = 1.f;
	float CurrentLockProgress = 0.f;
	
};
