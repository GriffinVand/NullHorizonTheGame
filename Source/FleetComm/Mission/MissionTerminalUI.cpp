#include "MissionTerminalUI.h"
#include "Components/VerticalBox.h"
#include "MissionData.h"
#include "MissionManager.h"
#include "MissionSelectionUI.h"
#include "ObjectiveDescriptionUI.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"

void UMissionTerminalUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (MissionInfoContainer)
	{
		MissionInfoContainer->SetVisibility(ESlateVisibility::Hidden);
	}
	InitializeMissionSelections();
}

void UMissionTerminalUI::InitializeMissionSelections()
{
	UE_LOG(LogTemp, Warning, TEXT("UMissionSelections Initialized"))
	if (UMissionManager* MissionManager = GetGameInstance()->GetSubsystem<UMissionManager>())
	{
		TArray<UMissionData*> MissionsToDisplay = MissionManager->AvailableMissions;
		if (MissionSelectionUIClass)
		{
			for (auto& Mission : MissionsToDisplay)
			{
				UE_LOG(LogTemp, Warning, TEXT("Mission Selection Displayed"));
				UMissionSelectionUI* NewMissionSelection = CreateWidget<UMissionSelectionUI>(this, MissionSelectionUIClass);
				NewMissionSelection->InitializeSelection(Mission);
				MissionScrollBox->AddChild(NewMissionSelection);
				NewMissionSelection->OnMissionSelectionHovered.AddDynamic(this, &UMissionTerminalUI::ShowMissionDescription);
			}
		}
	}
}

void UMissionTerminalUI::ShowMissionDescription(UMissionData* MissionData)
{
	if (MissionInfoContainer && ObjectiveDescriptionUIClass && MissionObjectivesScrollBox)
	{
		for (auto& Child : MissionObjectivesScrollBox->GetAllChildren())
		{
			Child->RemoveFromParent();
		}
		MissionName->SetText(FText::FromName(MissionData->MissionName));
		MissionDescription->SetText(MissionData->MissionDescription);
		for (auto ObjDefinition : MissionData->ObjectiveDefinitions)
		{
			UObjectiveDescriptionUI* NewObjectiveDescription = CreateWidget<UObjectiveDescriptionUI>(this, ObjectiveDescriptionUIClass);
			NewObjectiveDescription->InitializeObjectiveDescription(
				FText::FromName(ObjDefinition.ObjectiveName),
				ObjDefinition.ObjectiveDescription,
				UEnum::GetDisplayValueAsText(ObjDefinition.ObjectivePriority),
				ObjDefinition.ObjectiveRequiredProgressText);
			MissionObjectivesScrollBox->AddChild(NewObjectiveDescription);
		}
		MissionInfoContainer->SetVisibility(ESlateVisibility::Visible);
	}
}
