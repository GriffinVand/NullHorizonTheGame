#include "WeaponFireType.h"
#include "WeaponComponent.h"
#include "FleetComm/Weapons/WeaponTesting/TestDummy.h"
#include "FleetComm/Weapons/Projectiles/ProjectileLockOnInterface.h"

void UWeaponFireType::HandleFireOutput(UWeaponComponent* Owner, const FFireOutput& FireOutput)
{
	FString StateName = UEnum::GetValueAsString(FireOutput.FireState);
	switch (FireOutput.FireState)
	{
	case EFireState::StartFire:
		HandleFireStart(Owner, FireOutput);
		break;
	case EFireState::StopFire:
		HandleFireStop(Owner, FireOutput);
		break;
	case EFireState::Firing:
		HandleFire(Owner, FireOutput);
		break;
	case EFireState::Idle:
		break;
	default:
		break;
	}
}

void UWeaponFireType::InitializeFireType(UWeaponFireTypeData* FireTypeData)
{
	bReady = true;
	//Initialize Variables
}


void UProjectileFireType::HandleFire(UWeaponComponent* Owner, const FFireOutput& FireOutput)
{
	FRotator Direction = FireOutput.Direction;
	FVector Location = FireOutput.Origin;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = Owner->GetOwner();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
	for (int i = 0; i < ProjectileCount; i++)
	{
		AActor* NewProjectile = GetWorld()->SpawnActor<AActor>(
			ProjectileClass,
			Location,
			Direction,
			SpawnParameters);
		if (FireOutput.TargetActor != nullptr)
		{
			if (IProjectileLockOnInterface* PLI = Cast<IProjectileLockOnInterface>(NewProjectile))
			{
				PLI->SetHomingTarget(FireOutput.TargetActor);
			}
			else { UE_LOG(LogTemp, Error, TEXT("Homing target set but no IProjectileLockOnInterface UProjectileFireType::HandleFire")); }
		}
	}
}

void UProjectileFireType::InitializeFireType(UWeaponFireTypeData* FireTypeData)
{
	bReady = true;
	
	if (UProjectileFireTypeData* ProjectileFireTypeData = Cast<UProjectileFireTypeData>(FireTypeData))
	{
		ProjectileClass = ProjectileFireTypeData->ProjectileClass;
		ProjectileCount = ProjectileFireTypeData->ProjectileCount;
		ProjectileSpread = ProjectileFireTypeData->ProjectileOffsets;
	}
	else { UE_LOG(LogTemp, Error, TEXT("Could not cast to projectilefiretypedata from firetypedata UProjectileFireType::InitializeFireType")); }
}

void UBeamFireType::HandleFireStart(UWeaponComponent* Owner, const FFireOutput& FireOutput)
{
	
}

void UBeamFireType::HandleFireStop(UWeaponComponent* Owner, const FFireOutput& FireOutput)
{
	
}

void UBeamFireType::HandleFire(UWeaponComponent* Owner, const FFireOutput& FireOutput)
{
	
}




