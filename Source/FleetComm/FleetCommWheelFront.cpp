// Copyright Epic Games, Inc. All Rights Reserved.

#include "FleetCommWheelFront.h"
#include "UObject/ConstructorHelpers.h"

UFleetCommWheelFront::UFleetCommWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;
}