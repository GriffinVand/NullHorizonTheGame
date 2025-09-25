// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSlot.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "FleetComm/SaveFile.h"
#include "FleetComm/GameInstance/FleetcomGameInstance.h"
#include "Kismet/GameplayStatics.h"

void USaveSlot::InitializeSlot(FString FileName)
{
	
	SaveFileName = FileName;
	if (USaveFile* SaveFile = Cast<USaveFile>(UGameplayStatics::LoadGameFromSlot(SaveFileName, 0)))
	{
		const int32 IntTimePlayed = SaveFile->TimePlayed;
		const FString TimePlayed = FString::Printf(TEXT("%02d:%02d"), IntTimePlayed / 60, IntTimePlayed % 60);
		
		const FString LoadText = "Time Played: " + TimePlayed + "\nMoney: " + FString::FromInt(SaveFile->PlayerMoney);
		LoadInfo->SetText(FText::FromString(LoadText));
		FoundSaveFile = SaveFile;
		LoadSlotButton->OnClicked.AddDynamic(this, &USaveSlot::LoadGame);
	}
	else
	{
		const FString LoadText = "New Game";
		LoadInfo->SetText(FText::FromString(LoadText));
		LoadSlotButton->OnClicked.AddDynamic(this, &USaveSlot::NewGame);
	}
}

void USaveSlot::LoadGame()
{
	if (UFleetcomGameInstance* GameInstance = Cast<UFleetcomGameInstance>(GetWorld()->GetGameInstance()))
	{
		GameInstance->LoadGameSlot(FoundSaveFile);
	}
}

void USaveSlot::NewGame()
{
	USaveFile* NewSaveFile = Cast<USaveFile>(UGameplayStatics::CreateSaveGameObject(USaveFile::StaticClass()));
	if (UFleetcomGameInstance* GameInstance = Cast<UFleetcomGameInstance>(GetWorld()->GetGameInstance()))
	{
		GameInstance->NewGameSlot(NewSaveFile, SaveFileName);
	}
}

