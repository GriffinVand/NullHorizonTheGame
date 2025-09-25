#include "WeaponBaseUI.h"
#include "Kismet/GameplayStatics.h"
#include "FleetComm/Weapons/WeaponFramework/WeaponFireBehavior.h"

void UWeaponBaseUI::UpdateUI(TSharedPtr<FDefaultUIOutput> UIOutput)
{
	FDefaultUIOutput& DefaultUIOutput = *UIOutput;
	FText AmmoFullText = FText::FromString(FString::Printf(TEXT("%d / %d"),DefaultUIOutput.CurrentAmmo, DefaultUIOutput.MaxAmmo));
	AmmoText->SetText(AmmoFullText);
	float FireCooldown = DefaultUIOutput.CurrentFireDelay;
	ESlateVisibility Visible = FireCooldown > 0.f ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	FireCooldownText->SetVisibility(Visible);
	FireCooldownText->SetText(FText::AsNumber(FireCooldown));
	Visible = DefaultUIOutput.OverheatRate > 0.f ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	OverHeatProgressBar->SetVisibility(Visible);
	OverHeatProgressBar->SetPercent(DefaultUIOutput.CurrentHeatLevel);
	if (DefaultUIOutput.CurrentOverheatTime > 0.f)
	{
		OverHeatProgressBar->SetFillColorAndOpacity(FLinearColor::Red);
	}
	else { OverHeatProgressBar->SetFillColorAndOpacity(FLinearColor::Yellow); }
}

void UWeaponChargeUpUI::UpdateUI(TSharedPtr<FDefaultUIOutput> UIOutput)
{
	Super::UpdateUI(UIOutput);
	if (auto ChargeUpUIPtr = StaticCastSharedPtr<FChargeUpUIOutput>(UIOutput))
	{
		FChargeUpUIOutput& ChargeUpUIOutput = *ChargeUpUIPtr;
		ChargeProgressBar->SetPercent(ChargeUpUIOutput.CurrentChargeLevel);
	}
}

void UWeaponLockOnUI::UpdateUI(TSharedPtr<FDefaultUIOutput> UIOutput)
{
	Super::UpdateUI(UIOutput);
	if (auto LockOnUIPtr = StaticCastSharedPtr<FLockOnUIOutput>(UIOutput))
	{
		FLockOnUIOutput& LockOnUIOutput = *LockOnUIPtr;
		LockProgressBar->SetPercent(LockOnUIOutput.CurrentLockProgress);
		if (LockOnUIOutput.TargetActor != nullptr)
		{
			APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			FVector2D ScreenLocation = FVector2D::ZeroVector;
			FVector WorldLocation = LockOnUIOutput.TargetActor->GetActorLocation();
			PC->ProjectWorldLocationToScreen(WorldLocation, ScreenLocation);
			LockOnIndicator->SetVisibility(ESlateVisibility::Visible);
			LockOnIndicator->SetPositionInViewport(ScreenLocation);
			UE_LOG(LogTemp, Error, TEXT("New Lock Position %f / %f"), ScreenLocation.X, ScreenLocation.Y);
			
		}
		else { LockOnIndicator->SetVisibility(ESlateVisibility::Hidden); }
	}
}

void UWeaponLockOnUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (LockOnIndicatorClass)
	{
		LockOnIndicator = CreateWidget<ULockOnIndicatorWidget>(GetWorld(), LockOnIndicatorClass);
		if (LockOnIndicator)
		{
			LockOnIndicator->AddToViewport();
		}
	}
}



