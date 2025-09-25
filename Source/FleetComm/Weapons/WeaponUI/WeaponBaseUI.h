#pragma once
#include "CoreMinimal.h"
#include "LockOnIndicatorWidget.h"
#include "WeaponHUDInterface.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "WeaponBaseUI.generated.h"

UCLASS(Blueprintable)
class FLEETCOMM_API UWeaponBaseUI : public UUserWidget, public IWeaponHUDInterface
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UProgressBar* OverHeatProgressBar;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* AmmoText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* FireCooldownText;
	
	
	virtual void UpdateUI(TSharedPtr<FDefaultUIOutput> UIOutput) override;
	
};

UCLASS(Blueprintable)
class FLEETCOMM_API UWeaponLockOnUI : public UWeaponBaseUI
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ULockOnIndicatorWidget> LockOnIndicatorClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UProgressBar* LockProgressBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULockOnIndicatorWidget* LockOnIndicator;
	virtual void UpdateUI(TSharedPtr<FDefaultUIOutput> UIOutput) override;
	virtual void NativeConstruct() override;
	
};

UCLASS(Blueprintable)
class FLEETCOMM_API UWeaponChargeUpUI : public UWeaponBaseUI
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UProgressBar* ChargeProgressBar;
	
	virtual void UpdateUI(TSharedPtr<FDefaultUIOutput> UIOutput) override;
};
