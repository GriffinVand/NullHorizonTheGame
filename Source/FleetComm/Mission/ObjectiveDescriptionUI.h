#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveDescriptionUI.generated.h"

class UTextBlock;
class UVerticalBox;
class UHorizontalBox;

UCLASS(Blueprintable, BlueprintType)
class FLEETCOMM_API UObjectiveDescriptionUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitializeObjectiveDescription(
		FText ObjectiveNameText,
		FText ObjectiveDescriptionText,
		FText ObjectivePriorityText,
		FText ObjectiveRequiredProgressText);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UVerticalBox* VerticalContainer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UHorizontalBox* HeaderContainer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* ObjectiveName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* ObjectiveDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* ObjectivePriority;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* ObjectiveRequiredProgress;
	
};
