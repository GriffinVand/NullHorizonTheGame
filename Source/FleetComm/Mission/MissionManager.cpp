#include "MissionManager.h"
#include "Kismet/GameplayStatics.h"

void UMissionManager::NotifyEvent(FObjectiveData ObjData)
{
	for (const auto& Obj : ActiveObjectives)
	{
		Obj->NotifyEvent(ObjData);
	}
}

void UMissionManager::StartObjectives()
{
	for (const auto& Obj : CurrentMissionData->ObjectiveDefinitions)
	{
		if (TSubclassOf<UObjectiveBase> ObjClass = Obj.ObjectiveClass)
		{
			if (UObjectiveBase* NewObj = NewObject<UObjectiveBase>(ObjClass))
			{
				NewObj->ObjectivePriority = Obj.ObjectivePriority;
				NewObj->ObjectiveName = Obj.ObjectiveName;
				NewObj->ObjectiveDescription = Obj.ObjectiveDescription;
				NewObj->RequiredTags = Obj.RequiredTags;
				NewObj->CurrentState = EObjectiveState::Ongoing;
				NewObj->ObjectiveRequiredProgress = Obj.ObjectiveRequiredProgress;
				NewObj->ObjectiveXpReward = Obj.ObjectiveXpReward;
				NewObj->ObjectiveMoneyReward = Obj.ObjectiveMoneyReward;

				ActiveObjectives.Add(NewObj);
				NewObj->StartObjective();
				
			}
		}
	}
}

void UMissionManager::PrepareCurrentMission(UMissionData* MissionData)
{
	CurrentMissionData = MissionData;
}

void UMissionManager::StartMission(UMissionData* MissionToStart)
{
	CurrentMissionData = MissionToStart;
	if (CurrentMissionData && CurrentMissionData->MissionLevelName != NAME_None)
	{
		
		UGameplayStatics::OpenLevel(this, FName(CurrentMissionData->MissionLevelName));
	}
}

void UMissionManager::LoadAvailableMissions(TArray<TSoftObjectPtr<UMissionData>> AvailableMissionsToLoad)
{
	UE_LOG(LogTemp, Warning, TEXT("Missions to load length %d"), AvailableMissionsToLoad.Num());
	for (auto UnloadedMission : AvailableMissionsToLoad)
	{
		UE_LOG(LogTemp, Warning, TEXT("Loaded Mission"))
		AvailableMissions.Add(UnloadedMission.LoadSynchronous());
	}
}

void UMissionManager::HandleObjectiveStateChanged(EObjectiveState NewObjectiveState)
{
	//Checks if objective was primary and if all primary were completed then complete mission
	//Not sure yet if partial objective rewards are given even for failure
}


void UMissionManager::CompleteMission(bool Success)
{
	//Handles ending mission and alloting rewards to player
}
