#include "ProjectileLockOn.h"
#include "FleetComm/Weapons/WeaponTesting/TestDummy.h"

AProjectileLockOn::AProjectileLockOn()
{
	ProjectileMovementComponent->bIsHomingProjectile = false;
}


void AProjectileLockOn::SetHomingTarget(AActor* Target)
{
	UE_LOG(LogTemp, Error, TEXT("SetHomingTarget"));
	if (Target)
	{
		ProjectileMovementComponent->bIsHomingProjectile = true;
		ProjectileMovementComponent->HomingTargetComponent = Target->GetRootComponent();
	}
}

void AProjectileLockOn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ProjectileMovementComponent->HomingTargetComponent != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Homing Target %s ProjectileLockOn::Tick"), *ProjectileMovementComponent->HomingTargetComponent->GetOwner()->GetName());
	}
}

