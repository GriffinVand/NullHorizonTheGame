#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FleetComm/Weapons/WeaponData/WeaponDefinition.h"
#include "WeaponComponent.generated.h"

class UWeaponFireBehavior;
class UWeaponDefinition;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FLEETCOMM_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponDefinition* WeaponDefinitionData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponFireBehavior* WeaponFireBehavior;
	
	void FirePressed();
	void FireReleased();
	void FireWeapon(const FFireOutput& FireOutput);
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void HandleProjectileFire(const FFireOutput& FireOutput);
	void HandleHitScanFire(const FFireOutput& FireOutput);
	void HandleBeamFire(const FFireOutput& FireOutput);
};
