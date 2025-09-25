#pragma once

#include "CoreMinimal.h"
#include "ObjectiveBase.h"
#include "MissionData.h"
#include "MissionManager.generated.h"
UCLASS()

class FLEETCOMM_API UMissionManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override {}
	virtual void Deinitialize() override {}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UMissionData*> AvailableMissions;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMissionData* CurrentMissionData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UObjectiveBase*> ActiveObjectives;

	void LoadAvailableMissions(TArray<TSoftObjectPtr<UMissionData>> AvailableMissionsToLoad);
	void NotifyEvent(FObjectiveData ObjData);
	void StartMission(UMissionData* MissionToStart);
	void PrepareCurrentMission(UMissionData* MissionData);
	void CompleteMission(bool Success);
	void StartObjectives();
	UFUNCTION()
	void HandleObjectiveStateChanged(EObjectiveState NewObjectiveState);
private:

};
