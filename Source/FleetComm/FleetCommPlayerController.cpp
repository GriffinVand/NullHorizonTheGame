// Copyright Epic Games, Inc. All Rights Reserved.


#include "FleetCommPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Vehicles/SpaceShip.h"

void AFleetCommPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// // spawn the UI widget and add it to the viewport
	// VehicleUI = CreateWidget<UFleetCommUI>(this, VehicleUIClass);
	// check(VehicleUI);
	// VehicleUI->AddToViewport();
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

	// if (IsValid(VehiclePawn) && IsValid(VehicleUI))
	// {
	// 	VehicleUI->UpdateSpeed(VehiclePawn->GetChaosVehicleMovement()->GetForwardSpeed());
	// 	VehicleUI->UpdateGear(VehiclePawn->GetChaosVehicleMovement()->GetCurrentGear());
	// }
}

void AFleetCommPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ASpaceShip* ship = Cast<ASpaceShip>(InPawn))
	{
		ship->PossesShip(this);
	}

	//VehiclePawn = CastChecked<AFleetCommPawn>(InPawn);
}
