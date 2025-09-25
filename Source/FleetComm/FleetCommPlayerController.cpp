// Copyright Epic Games, Inc. All Rights Reserved.


#include "FleetCommPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Vehicles/SpaceShip.h"

void AFleetCommPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void AFleetCommPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void AFleetCommPlayerController::Tick(float Delta)
{
	Super::Tick(Delta);

}

void AFleetCommPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ASpaceShip* ship = Cast<ASpaceShip>(InPawn))
	{
		ship->PossesShip(this);
	}
}
