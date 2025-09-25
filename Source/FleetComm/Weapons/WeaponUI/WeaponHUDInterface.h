#pragma once
#include "CoreMinimal.h"
#include "WeaponHUDInterface.generated.h"

struct FChargeUpUIOutput;
struct FLockOnUIOutput;
struct FDefaultUIOutput;

UINTERFACE(MinimalAPI)
class UWeaponHUDInterface : public UInterface
{
	GENERATED_BODY()
public:
	
};

class IWeaponHUDInterface
{
	GENERATED_BODY()
public:
	virtual void UpdateUI(TSharedPtr<FDefaultUIOutput> UIOutput) {}
	
};
