#include "WeaponComponent.h"
#include "WeaponFireBehavior.h"
#include "WeaponFireType.h"
#include "FleetComm/Weapons/WeaponData/WeaponFireBehaviorData.h"
#include "FleetComm/Weapons/WeaponData/WeaponFireTypeData.h"
#include "FleetComm/Weapons/WeaponData/WeaponFireTypeData.h"
#include "TargetFinderComponent.h"
#include "Blueprint/UserWidget.h"
#include "FleetComm/Weapons/WeaponUI/WeaponHUDInterface.h"
#include "FleetComm/Weapons/WeaponUI/WeaponBaseUI.h"
#include "Kismet/KismetMathLibrary.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	if (WeaponDefinition)
    	{
			bProper = true;
    		WeaponFireBehavior = NewObject<UWeaponFireBehavior>(this, WeaponDefinition->WeaponFireBehaviorData->FireBehaviorClass);
    		WeaponFireType = NewObject<UWeaponFireType>(this, WeaponDefinition->WeaponFireTypeData->FireTypeClass);

    		InitializeFireBehavior();
    		InitializeFireType();
    	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Improper %s"), *GetOwner()->GetName());
	}
	
}

void UWeaponComponent::OnRegister()
{
	Super::OnRegister();

}


void UWeaponComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
}

void UWeaponComponent::OnActivate()
{
	if (bProper)
	{
		if (WeaponUIWidget)
		{
			WeaponUIWidget->RemoveFromParent();
		}
		if (WeaponDefinition->WeaponUIClass)
		{
			WeaponUIWidget = CreateWidget<UWeaponBaseUI>(GetWorld(), WeaponDefinition->WeaponUIClass);
			if (WeaponUIWidget)
			{
				WeaponUIWidget->AddToViewport();
			}
		}
	}
}

void UWeaponComponent::OnDeactivate()
{
	if (WeaponUIWidget) { WeaponUIWidget->RemoveFromParent(); }
}


void UWeaponComponent::UpdateUI()
{
	if (WeaponUIWidget)
	{
		if (IWeaponHUDInterface* WHI = Cast<IWeaponHUDInterface>(WeaponUIWidget))
		{
			WHI->UpdateUI(WeaponFireBehavior->GetUIOutput());
		}
		else { UE_LOG(LogTemp, Error, TEXT("UIWdiget does not implement correct interface UWeaponComponent::UpdateUI")); }
	}
	else { UE_LOG(LogTemp, Error, TEXT("WeaponUIWidget DNE UWeaponComponent::UpdateUI")); }
}

void UWeaponComponent::FirePressed()
{
	if (WeaponFireBehavior && WeaponFireBehavior->bReady)
	{
		WeaponFireBehavior->FirePressed(this);
	}
	else { UE_LOG(LogTemp, Error, TEXT("WeaponFireBehavior DNE UWeaponComponent::FirePressed")); }
}

void UWeaponComponent::FireReleased()
{
	if (WeaponFireBehavior && WeaponFireBehavior->bReady)
	{
		WeaponFireBehavior->FireReleased(this);
	}
	else { UE_LOG(LogTemp, Error, TEXT("WeaponFireBehavior DNE UWeaponComponent::FireReleased")); }
}

FFireTransform UWeaponComponent::GetFireTransform()
{
	FFireTransform FireTransform = FFireTransform();
	FVector Origin = BulletSpawnPoint->GetComponentLocation();
	FRotator Direction = BulletSpawnPoint->GetComponentRotation();
	FireTransform.Direction = Direction;
	FireTransform.Origin = Origin;
	return FireTransform;
}

void UWeaponComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bProper)
	{
		if (WeaponFireBehavior && WeaponFireType)
		{
			if (WeaponFireBehavior->bReady && WeaponFireType->bReady)
			{
				FFireOutput FireOutput = WeaponFireBehavior->UpdateBehavior(DeltaTime, this);
				FFireTransform FireTransform = GetFireTransform();
				FireOutput.Origin = FireTransform.Origin;
				FireOutput.Direction = FireTransform.Direction;
				WeaponFireType->HandleFireOutput(this, FireOutput);
				UpdateUI();
			}
			else { UE_LOG(LogTemp, Error, TEXT("Firebehavior or firetype not ready UWeaponComponent::TickComponent")); }
		}
		else { UE_LOG(LogTemp, Error, TEXT("Firebehavior or Firetype does not exist UWeaponComponent::TickComponent")); }
	}
}

void UWeaponComponent::InitializeFireBehavior()
{
	if (WeaponFireBehavior)
	{
		WeaponFireBehavior->InitializeBehavior(WeaponDefinition->WeaponFireBehaviorData, this);
	}
}

void UWeaponComponent::InitializeFireType()
{
	if (WeaponFireType)
	{
		WeaponFireType->InitializeFireType(WeaponDefinition->WeaponFireTypeData);
	}
}