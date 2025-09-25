// Copyright Epic Games, Inc. All Rights Reserved.

#include "FleetCommGameMode.h"
#include "FleetCommPlayerController.h"
#include "Weapons/ObjectPool.h"

AFleetCommGameMode::AFleetCommGameMode()
{
	PlayerControllerClass = AFleetCommPlayerController::StaticClass();

	TestBulletPool = CreateDefaultSubobject<UObjectPool>(TEXT("TestBulletPool"));
}
