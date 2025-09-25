// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveSlot.generated.h"

class UButton;
class UTextBlock;
class USaveFile;
/**
 * 
 */
UCLASS()
class FLEETCOMM_API USaveSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* LoadInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UButton* LoadSlotButton;

	UPROPERTY()
	FString SaveFileName;

	UPROPERTY()
	USaveFile* FoundSaveFile;

	UFUNCTION()
	void InitializeSlot(FString FileName);

	UFUNCTION()
	void LoadGame();

	UFUNCTION()
	void NewGame();
	
};
