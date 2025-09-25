#pragma once
#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectileLockOnInterface.h"
#include "ProjectileLockOn.generated.h"

class ATestDummy;

UCLASS(Blueprintable)
class FLEETCOMM_API AProjectileLockOn : public AProjectileBase, public IProjectileLockOnInterface
{
	GENERATED_BODY()
public:
	AProjectileLockOn();
	virtual void SetHomingTarget(AActor* Target) override;
	virtual void Tick(float DeltaTime) override;
	
};
