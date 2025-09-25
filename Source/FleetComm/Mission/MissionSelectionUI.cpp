#include "MissionSelectionUI.h"

#include "MissionManager.h"
#include "Components/Button.h"
#include "Fleetcomm/Mission/MissionData.h"
#include "Components/TextBlock.h"

void UMissionSelectionUI::InitializeSelection(UMissionData* CorrespondingMissionData)
{
	if (CorrespondingMissionData)
	{
		MissionData = CorrespondingMissionData;
		MissionTitle->SetText(FText::FromName(MissionData->MissionName));
		SelectButton->OnClicked.AddUniqueDynamic(this, &UMissionSelectionUI::MissionSelected);
		SelectButton->OnHovered.AddUniqueDynamic(this, &UMissionSelectionUI::MissionSelectionHovered);
		
	}
}

void UMissionSelectionUI::MissionSelected()
{
	UE_LOG(LogTemp, Display, TEXT("UMissionSelectionUI::MissionSelected()"))
	if (UMissionManager* MissionManager = GetGameInstance()->GetSubsystem<UMissionManager>())
	{
		MissionManager->StartMission(MissionData);
	}
}

void UMissionSelectionUI::MissionSelectionHovered()
{
	OnMissionSelectionHovered.Broadcast(MissionData);
}


