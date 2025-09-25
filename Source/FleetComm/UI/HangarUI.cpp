// Fill out your copyright notice in the Description page of Project Settings.


#include "HangarUI.h"
#include "../Vehicles/SpaceShip.h"
#include "Components/TextBlock.h"

void UHangarUI::UpdateSelection(const ASpaceShip* Ship)
{
	FText DisplayText = FText::FromString(Ship->ShipName + "\n\n" + Ship->ShipInfo); 
	InfoText->SetText(DisplayText);
}
