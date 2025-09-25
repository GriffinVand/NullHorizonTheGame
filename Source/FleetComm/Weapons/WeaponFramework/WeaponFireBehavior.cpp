#include "WeaponFireBehavior.h"

bool UWeaponFireBehavior::CanFire()
{
	return (Firing && !Overheated && CurrentFireDelay <= 0.f);
}


void UWeaponFireBehavior::UpdateFireCooldown(float DeltaTime)
{
	CurrentFireDelay = FMath::Max(CurrentFireDelay - DeltaTime, 0.f);
}


void UWeaponFireBehavior::UpdateHeatCooldown(float DeltaTime)
{
	if (Overheated)
	{
		CurrentOverheatTime = FMath::Max(CurrentOverheatTime - DeltaTime, 0.f);
		if (CurrentOverheatTime <= 0.f)
		{
			Overheated = false;
		}
	}
	else if (CurrentCooldownLevel > 0.f && !Firing)
	{
		CurrentCooldownLevel = FMath::Max(CurrentCooldownLevel -= CooldownRate * DeltaTime, 0.0f);
	}
}


void UDefaultFireBehavior::FirePressed(UWeaponComponent* Owner)
{
	Firing = true;
}

void UDefaultFireBehavior::FireReleased(UWeaponComponent* Owner)
{
	Firing = false;
}

void UDefaultFireBehavior::UpdateBehavior(float DeltaTime)
{
	UpdateHeatCooldown(DeltaTime);
	UpdateFireCooldown(DeltaTime);
}

FFireOutput UDefaultFireBehavior::TryFire(UWeaponComponent* Owner)
{
	FFireOutput FireOutput = FFireOutput();
	return FireOutput;
}





