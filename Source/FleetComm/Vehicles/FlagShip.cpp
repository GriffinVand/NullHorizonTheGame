// Fill out your copyright notice in the Description page of Project Settings.


#include "FlagShip.h"

#include "Components/Button.h"
#include "FleetComm/DockingEntrance.h"
#include "FleetComm/SaveFile.h"
#include "FleetComm/UI/HangarUI.h"
#include "Kismet/GameplayStatics.h"

AFlagShip::AFlagShip()
{
	HangarStorage.SetNum(HangarSize);
}

void AFlagShip::BeginPlay()
{
	Super::BeginPlay();

	if (USaveFile* SaveFile = Cast<USaveFile>(UGameplayStatics::LoadGameFromSlot("Test Slot 1", 0)))
	{
		HangarSize = SaveFile->HangarSize;
		HangarStorage.SetNum(HangarSize);
		HangarStorage = SaveFile->HangarStorage;
	}	
	HangarStorage.SetNum(HangarSize);

	TArray<USceneComponent*> ShipComponents;
	GetRootComponent()->GetChildrenComponents(true, ShipComponents);
	for (USceneComponent* Child : ShipComponents)
	{
		if (UDockingEntrance* DockingPoint = Cast<UDockingEntrance>(Child)) //Attach docking points
			DockingPoint->OnComponentBeginOverlap.AddDynamic(this, &AFlagShip::AttemptDock);
	}
}

void AFlagShip::AttemptDock(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASpaceShip* SpaceShip = Cast<ASpaceShip>(OtherActor))
	{
		if (SpaceShip == this) return; //Prevent ship from docking into itself
		Dock(SpaceShip);
	}
}

void AFlagShip::Dock(ASpaceShip* Ship)
{
	if (APlayerController* Pc = Cast<APlayerController>(Ship->GetController()))
	{
		Ship->UnpossesShip();
		Pc->UnPossess();
		Pc->Possess(this);
		//PossesShip(Pc);
		
		Ship->Destroy();
	}
}

void AFlagShip::OpenMenu()
{
	//if (!CurrentRotVelocity.IsNearlyZero() || !CurrentDirVelocity.IsNearlyZero()) return;
	Super::OpenMenu();
	//ShipMenuWidget = CreateWidget(Cast<APlayerController>(GetController()), ShipMenuClass);
	//ShipMenuWidget->AddToViewport();
	UHangarUI* HangarUI = Cast<UHangarUI>(ShipMenuWidget);
	SelectedShipIndex = 0;
	HangarStorage = Cast<USaveFile>(UGameplayStatics::LoadGameFromSlot("SaveFile1", 0))->HangarStorage;
	HangarUI->PreviousShipButton->OnClicked.AddDynamic(this, &AFlagShip::PreviousShip);
	HangarUI->NextShipButton->OnClicked.AddDynamic(this, &AFlagShip::NextShip);
	HangarUI->SelectButton->OnClicked.AddDynamic(this, &AFlagShip::SelectShip);
}

void AFlagShip::PreviousShip()
{
	int32 Temp = SelectedShipIndex;
	SelectedShipIndex--;
	if (SelectedShipIndex < 0) SelectedShipIndex = HangarSize - 1;
	while (HangarStorage[SelectedShipIndex] == nullptr)
	{
		SelectedShipIndex--;
		if (SelectedShipIndex < 0) SelectedShipIndex = HangarSize - 1;
		if (SelectedShipIndex == Temp) return;
	}
	Cast<UHangarUI>(ShipMenuWidget)->UpdateSelection(HangarStorage[SelectedShipIndex]);
}

void AFlagShip::NextShip()
{
	int32 Temp = SelectedShipIndex;
	SelectedShipIndex++;
	if (SelectedShipIndex >= HangarStorage.Num()) SelectedShipIndex = 0;
	while (HangarStorage[SelectedShipIndex] == nullptr)
	{
		SelectedShipIndex++;
		if (SelectedShipIndex >= HangarStorage.Num()) SelectedShipIndex = 0;
		if (SelectedShipIndex == Temp) return;
	}
	Cast<UHangarUI>(ShipMenuWidget)->UpdateSelection(HangarStorage[SelectedShipIndex]);
}

void AFlagShip::SelectShip()
{
	FVector Location = GetActorLocation() + (GetActorForwardVector() * 100);
	FRotator Rotation = GetActorRotation();
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ASpaceShip* Ship = GetWorld()->SpawnActor<ASpaceShip>(HangarStorage[SelectedShipIndex]->StaticClass(), Location, Rotation, SpawnInfo);
	if (Ship)
	{
		CloseMenu();
		this->UnpossesShip();
		GetController()->UnPossess();
		Ship->PossesShip(Cast<APlayerController>(GetController()));
	}
	
}

