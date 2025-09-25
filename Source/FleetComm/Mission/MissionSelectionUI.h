#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MissionSelectionUI.generated.h"

class UButton;
class UTextBlock;
class UMissionData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMissionSeledtionHovered, UMissionData*, MissionData);

UCLASS(Blueprintable, BlueprintType)
class FLEETCOMM_API UMissionSelectionUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitializeSelection(UMissionData* CorrespondingMissionData);

	UFUNCTION(BlueprintCallable)
	void MissionSelected();
	UFUNCTION(BlueprintCallable)
	void MissionSelectionHovered();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UButton* SelectButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* MissionTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMissionData* MissionData;

	UPROPERTY()
	FOnMissionSeledtionHovered OnMissionSelectionHovered;
	
};
