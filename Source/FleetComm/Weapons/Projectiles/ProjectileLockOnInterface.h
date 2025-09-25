#pragma once

#include "UObject/Interface.h"
#include "ProjectileLockOnInterface.generated.h"

UINTERFACE(MinimalAPI)
class UProjectileLockOnInterface : public UInterface
{
	GENERATED_BODY()
};

class IProjectileLockOnInterface
{
	GENERATED_BODY()

public:
	virtual void SetHomingTarget(AActor* Target) = 0;
};