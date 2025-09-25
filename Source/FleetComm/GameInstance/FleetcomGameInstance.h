#pragma once
#include "CoreMinimal.h"
#include "FleetComm/SaveFile.h"
#include "FleetcomGameInstance.generated.h"

UCLASS(BlueprintType, Blueprintable)

class FLEETCOMM_API UFleetcomGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual void Shutdown() override;
	void LoadGameSlot(USaveFile* SaveFile);
	void NewGameSlot(USaveFile* SaveFile, const FString& SaveFileName);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSoftObjectPtr<UMissionData>> DefaultMissionData;
	
};
