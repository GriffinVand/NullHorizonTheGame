// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Mission/MissionData.h"
#include "SaveFile.generated.h"

class ASpaceShip;
/**
 * 
 */
UCLASS(BlueprintType)
class FLEETCOMM_API USaveFile : public USaveGame
{
	GENERATED_BODY()

public:

	//Stats
	UPROPERTY()
	int32 TimePlayed = 0;
	UPROPERTY()
	int32 PlayerMoney = 50000;

	//
	UPROPERTY()
	FString PlayerLocation = "";

	//Inventory
	UPROPERTY()
	int32 HangarSize = 4;
	UPROPERTY()
	TArray<ASpaceShip*> HangarStorage;

	UPROPERTY(EditAnywhere)
	TArray<TSoftObjectPtr<UMissionData>> AvailableMissionsData;
	
	
};
