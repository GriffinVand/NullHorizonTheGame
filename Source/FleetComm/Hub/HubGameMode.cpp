#include "HubGameMode.h"
#include "FleetComm/Mission/MissionTerminalUI.h"

void AHubGameMode::BeginPlay()
{
	Super::BeginPlay();
	InitializeMissionTerminal();
}

void AHubGameMode::InitializeMissionTerminal()
{
	if (MissionTerminalUIClass)
	{
		MissionTerminalUI = CreateWidget<UMissionTerminalUI>(GetWorld()->GetFirstPlayerController(), MissionTerminalUIClass);
		if (MissionTerminalUI)
		{
			UE_LOG(LogTemp, Warning, TEXT("Add mission terminal ui to viewport from HubGameMode"));
			MissionTerminalUI->AddToViewport();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Couldn't find mission terminal UI"));
		}
	}
}