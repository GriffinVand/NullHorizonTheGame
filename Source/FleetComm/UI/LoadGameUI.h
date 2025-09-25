// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadGameUI.generated.h"

class USaveSlot;
class UButton;
/**
 * 
 */
UCLASS()
class FLEETCOMM_API ULoadGameUI : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString SaveFileName = "SaveFile";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	USaveSlot* SaveSlot1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UButton* DeleteSave1Button;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	USaveSlot* SaveSlot2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UButton* DeleteSave2Button;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	USaveSlot* SaveSlot3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UButton* DeleteSave3Button;

	UFUNCTION(BlueprintCallable)
	void LoadSaveSlots();
	
};
