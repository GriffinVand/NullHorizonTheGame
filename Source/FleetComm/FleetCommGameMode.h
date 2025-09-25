// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FleetCommGameMode.generated.h"

class UObjectPool;

UCLASS(MinimalAPI)
class AFleetCommGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFleetCommGameMode();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UObjectPool* TestBulletPool;
};



