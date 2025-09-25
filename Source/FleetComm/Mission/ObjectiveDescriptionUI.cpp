#include "ObjectiveDescriptionUI.h"
#include "Components/TextBlock.h"

void UObjectiveDescriptionUI::InitializeObjectiveDescription(FText ObjectiveNameText, FText ObjectiveDescriptionText, FText ObjectivePriorityText, FText ObjectiveRequiredProgressText)
{
	ObjectiveName->SetText(ObjectiveNameText);
	ObjectiveDescription->SetText(ObjectiveDescriptionText);
	const FString PriorityText = "(" + ObjectivePriorityText.ToString() + ")";
	ObjectivePriority->SetText(FText::FromString(PriorityText));
	ObjectiveRequiredProgress->SetText(ObjectiveRequiredProgressText);
}

