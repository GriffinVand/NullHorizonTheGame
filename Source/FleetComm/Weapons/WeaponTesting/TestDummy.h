#pragma once
#include "CoreMinimal.h"
#include "TestDummy.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FLEETCOMM_API ATestDummy : public AActor
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
};
