// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopComponent.h"

#include "SaveFile.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Vehicles/SpaceShip.h"
#include "FleetComm/DockingEntrance.h"
#include "UI/ShopUI.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UShopComponent::UShopComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShopComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	TArray<USceneComponent*> ShipComponents;
	GetOwner()->GetRootComponent()->GetChildrenComponents(true, ShipComponents);
	for (USceneComponent* Child : ShipComponents)
	{
		if (UDockingEntrance* DockingPoint = Cast<UDockingEntrance>(Child)) //Attach docking points
		{
			DockingPoint->OnComponentBeginOverlap.AddDynamic(this, &UShopComponent::OpenShop);
			DockingPoint->OnComponentEndOverlap.AddDynamic(this, &UShopComponent::CloseShop);
		}
	}
}

// Called every frame
void UShopComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UShopComponent::OpenShop(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASpaceShip* Ship = Cast<ASpaceShip>(OtherActor))
	{
		if (APlayerController* Pc = Cast<APlayerController>(Ship->GetController()))
		{
			DockedShip = Ship;
			Ship->UnpossesShip();
			ShopUIWidget = CreateWidget<UShopUI>(Pc, ShopUIClass);
			ShopUIWidget->AddToViewport();
			UpdateSelection(CurrentSelectionIndex);
			ShopUIWidget->BuyButton->OnClicked.AddDynamic(this, &UShopComponent::ConfirmSelection);
			ShopUIWidget->CloseShopButton->OnClicked.AddDynamic(this, &UShopComponent::CloseShopButton);
		}
	}
}

void UShopComponent::CloseShop(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!ShopUIWidget) return;
	if (ASpaceShip* Ship = Cast<ASpaceShip>(OtherActor))
	{
		if (APlayerController* Pc = Cast<APlayerController>(Ship->GetController()))
		{
			
			Ship->PossesShip(Pc);
			ShopUIWidget->RemoveFromParent();
			CurrentSelectionIndex = 0;
			DockedShip = nullptr;
		}
	}
}

void UShopComponent::CloseShopButton()
{
	if (DockedShip)
	{
		if (APlayerController* Pc = Cast<APlayerController>(DockedShip->GetController()))
		{
			DockedShip->PossesShip(Pc);
			ShopUIWidget->RemoveFromParent();
			CurrentSelectionIndex = 0;
			DockedShip = nullptr;
		}
	}
}

void UShopComponent::PreviousSelection()
{
	int32 TempIndex = CurrentSelectionIndex--;
	if (TempIndex < 0) TempIndex = Catalogue.Num() - 1;
	if (TempIndex != CurrentSelectionIndex)
	{
		CurrentSelectionIndex = TempIndex;
		UpdateSelection(CurrentSelectionIndex);
	}
}

void UShopComponent::NextSelection()
{
	int32 TempIndex = CurrentSelectionIndex++;
	if (TempIndex >= Catalogue.Num()) TempIndex = 0;
	if (TempIndex != CurrentSelectionIndex)
	{
		CurrentSelectionIndex = TempIndex;
		UpdateSelection(CurrentSelectionIndex);
	}
}

void UShopComponent::ConfirmSelection()
{
	auto [Ship, Price] = Catalogue[CurrentSelectionIndex];
	if (USaveFile* SaveFile = Cast<USaveFile>(UGameplayStatics::LoadGameFromSlot(SaveTestLocation, 0)))
	{
		int32 PopulatedSlots = 0;
		for (ASpaceShip* TempShip : SaveFile->HangarStorage)
		{
			if (IsValid(TempShip)) ++PopulatedSlots;
		}
		if ((SaveFile->PlayerMoney < Price) || (PopulatedSlots >= SaveFile->HangarSize)) return;

		SaveFile->PlayerMoney -= Price;
		ShopUIWidget->PlayerMoneyText->SetText(FText::FromString(FString::FromInt(SaveFile->PlayerMoney)));

		const FVector& Location = FVector(1000, 1000, 1000);
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		UWorld* World = GetWorld();
		ASpaceShip* Actor = World->SpawnActor<ASpaceShip>(Ship, Location, FRotator::ZeroRotator, SpawnInfo);
		
		SaveFile->HangarStorage.Add(Actor);

		UGameplayStatics::AsyncSaveGameToSlot(SaveFile, SaveTestLocation, 0);
	}
}


void UShopComponent::UpdateSelection(int32 Index)
{
	if (!ShopUIWidget) return;
	ShopUIWidget->UpdateUI(Catalogue[Index]);
}


