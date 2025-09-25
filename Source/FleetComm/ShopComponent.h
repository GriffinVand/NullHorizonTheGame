// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShopComponent.generated.h"

class UShopUI;
class AFleetCommPlayerController;
class ASpaceShip;

USTRUCT(BlueprintType)
struct FShopOption
{
	GENERATED_BODY()

	// Declare your member variables here
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyStruct")
	TSubclassOf<ASpaceShip> Ship;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyStruct")
	int32 Price;  
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLEETCOMM_API UShopComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShopComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	virtual void OpenShop(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	virtual void CloseShop(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	virtual void CloseShopButton();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FShopOption> Catalogue;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UShopUI> ShopUIClass;

	UFUNCTION(BlueprintCallable)
	void PreviousSelection();
	UFUNCTION(BlueprintCallable)
	void NextSelection();
	UFUNCTION(BlueprintCallable)
	void ConfirmSelection();

private:
	void UpdateSelection(int32 Index);

	int32 CurrentSelectionIndex = 0;

	FString SaveTestLocation = "SaveFile1";

private:
	UPROPERTY()
	UShopUI* ShopUIWidget;

	UPROPERTY()
	ASpaceShip* DockedShip;
};
