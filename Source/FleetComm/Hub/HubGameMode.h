#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Gamemode.h"
#include "HubGameMode.generated.h"

class UMissionTerminalUI;

UCLASS(Blueprintable)
class FLEETCOMM_API AHubGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	void BeginPlay() override;
	void InitializeMissionTerminal();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMissionTerminalUI* MissionTerminalUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UMissionTerminalUI> MissionTerminalUIClass;
	
	
};
