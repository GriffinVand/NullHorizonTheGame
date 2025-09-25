
#include "ObjectPool.h"

#include "PoolableActor.h"
#include "Engine/World.h"

void UObjectPool::BeginPlay()
{
	Super::BeginPlay();
	InitializePool();
}


void UObjectPool::AddToPool(const int32& Count)
{
	const FVector& Location = FVector(1000, 1000, 1000);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	UWorld* World = GetWorld();

	for (int i = 0; i < Count; i++)
	{
		APoolableActor* Actor = World->SpawnActor<APoolableActor>(ObjectClass, Location, FRotator::ZeroRotator, SpawnInfo);
		if (!Actor)
		{
			return;
		}
		ObjectPool.Add(Actor);
		Actor->ReturnToPool();
	}
}

void UObjectPool::InitializePool()
{
	AddToPool(DefaultSize);
}

APoolableActor* UObjectPool::GetFirst()
{
	for (APoolableActor* Actor : ObjectPool)
	{
		if (Actor->IsPooled) return Actor;
	}
	AddToPool(AddAmount);
	return GetFirst();//ObjectPool[ObjectPool.Num() - AddAmount]; // Grabs first added actor
}

APoolableActor* UObjectPool::RetrievePooledObject(const FTransform& Transform)
{
	APoolableActor* Actor = GetFirst();
	Actor->SetActorTransform(Transform);
	Actor->SetActive(true);
	Actor->IsPooled = false;
	return Actor;
}

APoolableActor* UObjectPool::RetrievePooledObject(const FVector& Location, const FRotator& Rotation)
{
	APoolableActor* Actor = GetFirst();
	Actor->SetActorLocationAndRotation(Location, Rotation);
	Actor->SetActive(true);
	Actor->IsPooled = false;
	return Actor;
}


