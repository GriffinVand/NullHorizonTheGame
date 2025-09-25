// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopUI.generated.h"

struct FShopOption;
class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class FLEETCOMM_API UShopUI : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* InfoText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PlayerMoneyText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UButton* BuyButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UButton* CloseShopButton;

	UFUNCTION(BlueprintCallable)
	void UpdateUI(FShopOption Info);
};
