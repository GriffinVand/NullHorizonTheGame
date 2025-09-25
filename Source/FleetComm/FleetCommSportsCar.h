// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FleetCommPawn.h"
#include "FleetCommSportsCar.generated.h"

/**
 *  Sports car wheeled vehicle implementation
 */
UCLASS(abstract)
class FLEETCOMM_API AFleetCommSportsCar : public AFleetCommPawn
{
	GENERATED_BODY()
	
public:

	AFleetCommSportsCar();
};
