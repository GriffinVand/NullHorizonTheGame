#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MissionTerminalUI.generated.h"

class UScrollBox;
class UObjectiveDescriptionUI;
class UVerticalBox;
class UMissionSelectionUI;
class UTextBlock;
class UMissionData;

UCLASS(Blueprintable, BlueprintType)
class FLEETCOMM_API UMissionTerminalUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	void InitializeMissionSelections();
	
	UFUNCTION(BlueprintCallable)
	void ShowMissionDescription(UMissionData* MissionData);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UMissionSelectionUI> MissionSelectionUIClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UObjectiveDescriptionUI> ObjectiveDescriptionUIClass;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UScrollBox* MissionScrollBox;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UVerticalBox* MissionInfoContainer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UScrollBox* MissionObjectivesScrollBox;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* MissionName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* MissionDescription;
	
	
};
