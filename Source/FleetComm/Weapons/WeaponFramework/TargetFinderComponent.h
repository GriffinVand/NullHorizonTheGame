#pragma once
#include "CoreMinimal.h"
#include "TargetFinderComponent.generated.h"

class ATestDummy;

UCLASS(Blueprintable, BlueprintType)
class FLEETCOMM_API UTargetFinderComponent : public USceneComponent
{
	GENERATED_BODY()
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
	bool IsTargetValid(ATestDummy* Target);
	ATestDummy* GetTarget();
	
	
};
