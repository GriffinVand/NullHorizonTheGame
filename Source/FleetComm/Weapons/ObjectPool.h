// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPool.generated.h"


class APoolableActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLEETCOMM_API UObjectPool : public UActorComponent
{
	GENERATED_BODY()

public:	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ObjectPool")
	int32 DefaultSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ObjectPool")
	int32 MaxSize = -1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ObjectPool")
	int32 AddAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ObjectPool")
	TSubclassOf<APoolableActor> ObjectClass;

	UPROPERTY()
	TArray<APoolableActor*> ObjectPool;

private:
	void InitializePool();
	void AddToPool(const int32& Count);
	APoolableActor* GetFirst();

public:
	UFUNCTION()
	APoolableActor* RetrievePooledObject(const FTransform& Transform);
	APoolableActor* RetrievePooledObject(const FVector& Location, const FRotator& Rotation);
		
};