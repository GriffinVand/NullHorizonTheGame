// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopUI.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "FleetComm/ShopComponent.h"
#include "FleetComm/Vehicles/SpaceShip.h"


void UShopUI::UpdateUI(FShopOption Info)
{
	const FVector& Location = FVector(1000, 1000, 1000);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	UWorld* World = GetWorld();
	ASpaceShip* Ship = World->SpawnActor<ASpaceShip>(Info.Ship, Location, FRotator::ZeroRotator, SpawnInfo);
	
	const FString InfoBoxText = Ship->ShipName + "\n\n" +
		FString::FromInt(Info.Price) + "\n\n" +
		Ship->ShipInfo;
	InfoText->SetText(FText::FromString(InfoBoxText));
}
