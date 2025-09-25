#include "FleetcomGameInstance.h"

#include "FleetComm/Mission/MissionManager.h"
#include "Kismet/GameplayStatics.h"

void UFleetcomGameInstance::Init()
{
	Super::Init();
}

void UFleetcomGameInstance::Shutdown()
{
	Super::Shutdown();
}

void UFleetcomGameInstance::LoadGameSlot(USaveFile* SaveFile)
{
	if (UMissionManager* MissionManager = GetSubsystem<UMissionManager>())
	{
		FString LevelToLoad = SaveFile->PlayerLocation;
		UE_LOG(LogTemp, Warning, TEXT("Tell mission manager load missions"));
		MissionManager->LoadAvailableMissions(DefaultMissionData);
		//MissionManager->LoadAvailableMissions(SaveFile->AvailableMissionsData);
		FString StartLevel = "Hub_Level";
		UGameplayStatics::OpenLevel(this, FName(StartLevel)); 
		//UGameplayStatics::OpenLevel(this, FName(LevelToLoad));
		return;
	}
	UE_LOG(LogTemp, Error, TEXT("No mission manager found! UFleetcomGameInstance::LoadGameSlot"))
}

void UFleetcomGameInstance::NewGameSlot(USaveFile* SaveFile, const FString& SaveFileName)
{
	//Tell mission manager to create default available missions
	if (UMissionManager* MissionManager = GetSubsystem<UMissionManager>())
	{
		UGameplayStatics::SaveGameToSlot(SaveFile, SaveFileName, 0);
		MissionManager->LoadAvailableMissions(DefaultMissionData);
		FString NewGameStartLevel = "Hub_Level";
		UGameplayStatics::OpenLevel(this, FName(NewGameStartLevel));
		return;
	}
	UE_LOG(LogTemp, Error, TEXT("No mission manager found! UFleetcomGameInstance::LoadGameSlot"))

}
