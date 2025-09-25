#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolableActor.generated.h"

UCLASS()
class FLEETCOMM_API APoolableActor : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	bool IsPooled = false;

	virtual void SetActive(const bool& IsActive);
	
	UFUNCTION()
	void ReturnToPool()
	{
		IsPooled = true;
		SetActive(false);
	};
	
};
