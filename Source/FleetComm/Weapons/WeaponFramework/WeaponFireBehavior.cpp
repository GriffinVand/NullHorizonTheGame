#include "WeaponFireBehavior.h"

#include "TargetFinderComponent.h"
#include "WeaponComponent.h"
#include "FleetComm/Weapons/WeaponData/WeaponFireBehaviorData.h"
#include "FleetComm/Weapons/WeaponTesting/TestDummy.h"

void UWeaponFireBehavior::FirePressed(UWeaponComponent* Owner)
{
	bFireHeld = true;
	if (!bStartFire)
	bStartFire = true;
}

void UWeaponFireBehavior::FireReleased(UWeaponComponent* Owner)
{
	bFireHeld = false;
	if (!bStopFire)
	bStopFire = true;
}

void UWeaponFireBehavior::InitializeBehavior(UWeaponFireBehaviorData* BehaviorData, UWeaponComponent* Owner)
{
	bReady = true;
	
	Automatic = BehaviorData->Automatic;
	FireRate = BehaviorData->FireRate;
	CooldownRate = BehaviorData->CooldownRate;
	OverheatRate = BehaviorData->OverheatRate;
	OverheatRepairTime = BehaviorData->OverheatDelay;

	MaxAmmo = BehaviorData->MaxAmmo;
	CurrentAmmo = MaxAmmo;
	AmmoCost = BehaviorData->AmmoCost;
}

FFireOutput UWeaponFireBehavior::UpdateBehavior(float DeltaTime, UWeaponComponent* Owner)
{
	UpdateHeatCooldown(DeltaTime);
	UpdateFireCooldown(DeltaTime);

	FFireOutput FireOutput = FFireOutput();
	if (bFireHeld && CanFire())
	{
		if (bStartFire)
		{
			FireOutput.FireState = EFireState::StartFire;
			bFiring = true;
			bStartFire = false;
		}
		else
		{
			FireOutput.FireState = EFireState::Firing;
		}
		OnFire();
	}
	else if (bStopFire)
	{
		FireOutput.FireState = EFireState::StopFire;
		bFiring = false;
		bStopFire = false;
	}
	else { FireOutput.FireState = EFireState::Idle; }
	return FireOutput;
}

TSharedPtr<FDefaultUIOutput> UWeaponFireBehavior::GetUIOutput()
{
	TSharedPtr<FDefaultUIOutput> UIOutput = MakeShared<FDefaultUIOutput>();
	FillDefaultUIOutput(*UIOutput);
	return UIOutput;
}

void UWeaponFireBehavior::FillDefaultUIOutput(FDefaultUIOutput& UIOutput)
{
	UIOutput.CurrentFireDelay =  CurrentFireDelay;
	UIOutput.MaxAmmo = MaxAmmo;
	UIOutput.CurrentAmmo = CurrentAmmo;
	UIOutput.CurrentHeatLevel = CurrentHeatLevel;
	UIOutput.OverheatRate = OverheatRate;
	UIOutput.CurrentOverheatTime = CurrentOverheatTime;
}



void UWeaponFireBehavior::OnFire()
{
	ApplyHeat();
	CurrentFireDelay = FireRate;
	CurrentAmmo -= AmmoCost;
}

bool UWeaponFireBehavior::CanFire()
{
	return (!Overheated && CurrentFireDelay <= 0.f && CurrentAmmo >= AmmoCost);
}


void UWeaponFireBehavior::UpdateFireCooldown(float DeltaTime)
{
	if (!Overheated && CurrentFireDelay > 0.f)
	{
		CurrentFireDelay = FMath::Max(CurrentFireDelay - DeltaTime, 0.f);
	}
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
	else if (CurrentHeatLevel > 0.f && !bFireHeld)
	{
		CurrentHeatLevel = FMath::Max(CurrentHeatLevel - CooldownRate * DeltaTime, 0.0f);
	}
}

void UWeaponFireBehavior::ApplyHeat()
{
	CurrentHeatLevel = FMath::Min(CurrentHeatLevel + OverheatRate, 1.f);
	if (CurrentHeatLevel >= 1.f)
	{
		Overheated = true;
		CurrentOverheatTime = OverheatRepairTime;
	}
}

//
//Charge-up Behavior
//

void UChargeUpFireBehavior::InitializeBehavior(UWeaponFireBehaviorData* BehaviorData, UWeaponComponent* Owner)
{
	Super::InitializeBehavior(BehaviorData, Owner);

	if (UChargeUpBehaviorData* ChargeUpBehaviorData = Cast<UChargeUpBehaviorData>(BehaviorData))
	{
		ChargeRate = ChargeUpBehaviorData->ChargeRate;
		ChargeDecayRate = ChargeUpBehaviorData->ChargeDecayRate;
		ChargeLostPerShot = ChargeUpBehaviorData->ChargeLostPerShot;
	}
	else { UE_LOG(LogTemp, Error, TEXT("Non ChargeUpBehaviorData passed to ChargeUpBehavior UChargeUpFireBehavior::InitializeBehavior")); }
}


FFireOutput UChargeUpFireBehavior::UpdateBehavior(float DeltaTime, UWeaponComponent* Owner)
{
	UpdateHeatCooldown(DeltaTime);
	UpdateFireCooldown(DeltaTime);
	UpdateChargeLevel(DeltaTime);

	FFireOutput FireOutput = FFireOutput();
	if (bStopFire)
	{
		FireOutput.FireState = EFireState::StopFire;
		bFiring = false;
		bStopFire = false;
		UE_LOG(LogTemp, Error, TEXT("Stop Fire"));
	}
	else if (bFireHeld && CanFire())
	{
		if (bStartFire)
		{
			FireOutput.FireState = EFireState::StartFire;
			bFiring = true;
			bStartFire = false;
		}
		else
		{
			FireOutput.FireState = EFireState::Firing;
		}
		OnFire();
	}
	else { FireOutput.FireState = EFireState::Idle; }
	return FireOutput;
}

void UChargeUpFireBehavior::UpdateChargeLevel(float DeltaTime)
{
	if (bFiring)
	{
		//No action needed Onfire() will decrement charge
	}
	else if (!bFiring && bFireHeld && CurrentFireDelay <= 0.f && CurrentAmmo >= AmmoCost)
	{
		CurrentChargeLevel = FMath::Min(CurrentChargeLevel + (DeltaTime * ChargeRate), 1.f);
	}
	else if  (!bFiring)
	{
		CurrentChargeLevel = FMath::Max(CurrentChargeLevel - (DeltaTime * ChargeDecayRate), 0.f);
	}
}

TSharedPtr<FDefaultUIOutput> UChargeUpFireBehavior::GetUIOutput()
{
	TSharedPtr<FChargeUpUIOutput> UIOutput = MakeShared<FChargeUpUIOutput>();
	FillDefaultUIOutput(*UIOutput);
	UIOutput->CurrentChargeLevel = CurrentChargeLevel;
	return UIOutput;
	
}

bool UChargeUpFireBehavior::CanFire()
{
	
	return ((CurrentChargeLevel >= 1.f || (bFiring && CurrentChargeLevel > 0.f)) && CurrentAmmo >= AmmoCost && CurrentFireDelay <= 0.f);
}

void UChargeUpFireBehavior::OnFire()
{
	Super::OnFire();
	ApplyChargeCost();
}

void UChargeUpFireBehavior::ApplyChargeCost()
{
	CurrentChargeLevel = FMath::Max(CurrentChargeLevel - ChargeLostPerShot, 0.f);
}

//
//Lock-on Behavior
//

void ULockOnFireBehavior::InitializeBehavior(UWeaponFireBehaviorData* BehaviorData, UWeaponComponent* Owner)
{
	Super::InitializeBehavior(BehaviorData, Owner);
	if (ULockOnFireBehaviorData* LockOnBehaviorData = Cast<ULockOnFireBehaviorData>(BehaviorData))
	{
		LockRate = LockOnBehaviorData->LockRate;
		ShotsPerLock = LockOnBehaviorData->ShotsPerLock;
	}
	else { UE_LOG(LogTemp, Error, TEXT("Non-LockOnBehaviorData passed to LockOnBehavior ULockOnBehavior::InitializeBehavior")); }
	if (UTargetFinderComponent* TargetFinder = Owner->TargetFinderComp)
	{
		TargetFinderComp = TargetFinder;
	}
	else { UE_LOG(LogTemp, Error, TEXT("Target finder component not found ULockOnFireBehavior::InitializeBehavior")); }

}

FFireOutput ULockOnFireBehavior::UpdateBehavior(float DeltaTime, UWeaponComponent* Owner)
{
	UpdateFireCooldown(DeltaTime);
	UpdateHeatCooldown(DeltaTime);
	UpdateLockProgress(DeltaTime);
	FFireOutput FireOutput = FFireOutput();
	if (bFireHeld && CanFire())
	{
		if (bStartFire)
		{
			FireOutput.FireState = EFireState::StartFire;
			bFiring = true;
			bStartFire = false;
		}
		else
		{
			FireOutput.FireState = EFireState::Firing;
		}
		FireOutput.TargetActor = TargetDummy;
		OnFire();
	}
	else { FireOutput.FireState = EFireState::Idle; }
	return FireOutput;
	
}

void ULockOnFireBehavior::FirePressed(UWeaponComponent* Owner)
{
	bFireHeld = true;
	bStartFire = true;
	TryStartLock(Owner);
}

void ULockOnFireBehavior::FireReleased(UWeaponComponent* Owner)
{
	bFireHeld = false;
	bStopFire = true;
	TargetDummy = nullptr;
}

bool ULockOnFireBehavior::CanFire()
{
	return (CurrentLockProgress >= 1.f);
}

void ULockOnFireBehavior::OnFire()
{
	ApplyHeat();
	UE_LOG(LogTemp, Error, TEXT("ULockOnFireBehavior::OnFire"));
	bLocking = false;
	CurrentLockProgress = 0.f;
	TargetDummy = nullptr;
	CurrentFireDelay = FireRate;
	CurrentAmmo -= AmmoCost;
	
}

void ULockOnFireBehavior::TryStartLock(UWeaponComponent* Owner)
{
	if (CurrentFireDelay <= 0.f && CurrentAmmo >= AmmoCost)
	{
		TargetDummy = TargetFinderComp->GetTarget();
		if (TargetDummy != nullptr)
		{
			bLocking = true;
			UE_LOG(LogTemp, Error, TEXT("TargetFound %s = ULockOnFireBehavior::TryStartLock"), *TargetDummy->GetName());
		}
		else { UE_LOG(LogTemp, Error, TEXT("No target found ULockOnFireBehavior::TryStartLock")); }
	}
}

void ULockOnFireBehavior::UpdateLockProgress(float DeltaTime)
{
	if (bLocking && bFireHeld && TargetFinderComp->IsTargetValid(TargetDummy))
	{
		CurrentLockProgress = FMath::Min(CurrentLockProgress + LockRate*DeltaTime, 1.f);
	}
	else
	{
		bLocking = false;
		TargetDummy = nullptr;
		CurrentLockProgress = 0.f;
	}
}

TSharedPtr<FDefaultUIOutput> ULockOnFireBehavior::GetUIOutput()
{
	TSharedPtr<FLockOnUIOutput> UIOutput = MakeShared<FLockOnUIOutput>();
	FillDefaultUIOutput(*UIOutput);
	UIOutput->CurrentLockProgress = CurrentLockProgress;
	UIOutput->TargetActor = TargetDummy;
	return UIOutput;
}












