
#include "PoolableActor.h"

void APoolableActor::SetActive(const bool& IsActive)
{
	SetActorEnableCollision(IsActive);
	SetActorHiddenInGame(!IsActive);
	SetActorTickEnabled(IsActive);
}

