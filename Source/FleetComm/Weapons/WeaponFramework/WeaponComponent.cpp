#include "WeaponComponent.h"
#include "WeaponFireBehavior.h"
#include "Kismet/KismetMathLibrary.h"

void UWeaponComponent::FirePressed()
{
	WeaponFireBehavior->FirePressed(this);
}

void UWeaponComponent::FireReleased()
{
	WeaponFireBehavior->FireReleased(this);
}



void UWeaponComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (WeaponFireBehavior->CanFire())
	{
		FireWeapon(WeaponFireBehavior->TryFire(this));
	}
}

void UWeaponComponent::FireWeapon(const FFireOutput& FireOutput)
{
	switch (FireOutput.FireType)
	{
	case EFireType::Projectile:
		HandleProjectileFire(FireOutput);
		break;
	case EFireType::Beam:
		break;
	case EFireType::Hitscan:
		break;
	default:
		break;
	}
}

void UWeaponComponent::HandleProjectileFire(const FFireOutput& FireOutput)
{
	FVector Direction = FireOutput.Direction;
	FVector Location = FireOutput.Origin;
	TSubclassOf<AActor> ProjectileClass = WeaponDefinitionData->ProjectileSubClass;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
	for (int i = 0; i < FireOutput.ProjectileCount; i++)
	{
		AActor* NewProjectile = GetWorld()->SpawnActor<AActor>(
			ProjectileClass,
			Location,
			Direction.Rotation(),
			SpawnParameters);
	}
}

void UWeaponComponent::HandleHitScanFire(const FFireOutput& FireOutput)
{
	
}

void UWeaponComponent::HandleBeamFire(const FFireOutput& FireOutput)
{
	
}


