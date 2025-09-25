#pragma once
#include "CoreMinimal.h"
#include "ObjectiveBase.h"
#include "MissionData.generated.h"

USTRUCT(BlueprintType)
struct FObjectiveDefinition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UObjectiveBase> ObjectiveClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ObjectiveName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ObjectiveDescription;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer RequiredTags;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ObjectiveRequiredProgress;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ObjectiveMoneyReward;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ObjectiveXpReward;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EObjectivePriority ObjectivePriority;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ObjectiveRequiredProgressText;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ObjectiveCurrentProgressText;
};

UCLASS(BlueprintType)
class UMissionData : public UDataAsset
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MissionName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MissionDescription;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FObjectiveDefinition> ObjectiveDefinitions;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MissionLevelName;

	
	
};
