#pragma once

#include "CoreMinimal.h"
#include "GameplayTagcontainer.h"
#include "ObjectiveBase.generated.h"

//Allows mission manager to distinguish between which objectives are necessary for victory or optional
UENUM(Blueprintable)
enum class EObjectivePriority : uint8
{
	Primary UMETA(DisplayName = "Primary"),
	Secondary UMETA(DisplayName = "Secondary"),
};

//Used by mission manager to determine which objectives the player has succeeded in
UENUM(Blueprintable)
enum class EObjectiveState : uint8
{
	Ongoing UMETA(DisplayName = "Ongoing"),
	Succeeded UMETA(DisplayName = "Completed"),
	Failed  UMETA(DisplayName = "Failed"),
	Inactive UMETA(DisplayName = "Inactive"),
};

//Generic struct to allow objectives to receive events
USTRUCT(BlueprintType)
struct FObjectiveData
{
	GENERATED_BODY()
	//A group of specific tags used to check if an objective's exact conditions are met
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer Tags;
	//Progress increment if necessary
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Progress;
	//Who is the origin of this data(could be helpful)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Instigator;
};

//Allows the objective to broadcast to the mission manager when its state changes ie: complete/failed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveStateChanged, EObjectiveState, NewState);

UCLASS()
class FLEETCOMM_API UObjectiveBase : public UObject
{
	GENERATED_BODY()
	
public:
	
	//Called on objective by MissionManager when MissionManager receives objective related events
	virtual void NotifyEvent(FObjectiveData ObjData);
	virtual void UpdateUI();
	virtual void StartObjective();
	virtual void ObjectiveStateChanged(EObjectiveState NewObjectiveState);

	//Subscribable delegate used by MissionManager
	FOnObjectiveStateChanged OnObjectiveStateChanged_Delegate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer RequiredTags = FGameplayTagContainer();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EObjectiveState CurrentState = EObjectiveState::Inactive;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ObjectiveName = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ObjectiveDescription = FText::FromString(TEXT("None"));
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EObjectivePriority ObjectivePriority = EObjectivePriority::Primary;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ObjectiveRequiredProgress = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ObjectiveCurrentProgress = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ObjectiveXpReward = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ObjectiveMoneyReward = 0;
	
	
	
};
