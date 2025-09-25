// Copyright Epic Games, Inc. All Rights Reserved.

#include "FleetCommWheelRear.h"
#include "UObject/ConstructorHelpers.h"

UFleetCommWheelRear::UFleetCommWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;
}