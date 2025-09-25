// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceShip.h"
#include "FlagShip.generated.h"

class USphereComponent;
/**
 * 
 */
UCLASS(Blueprintable)
class FLEETCOMM_API AFlagShip : public ASpaceShip
{
	GENERATED_BODY()

public:

	AFlagShip();

	//Hangar stuff. Move to separate component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hangar")
	int32 HangarSize = 4;
	UPROPERTY()
	TArray<ASpaceShip*> HangarStorage;
	UFUNCTION()
	void SelectShip();
	UFUNCTION()
	void NextShip();
	UFUNCTION()
	void PreviousShip();
	int32 SelectedShipIndex;


protected:
	UFUNCTION()
	virtual void Dock(ASpaceShip* Ship);


	virtual void OpenMenu() override;

	UFUNCTION()
	virtual void AttemptDock(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;
};
