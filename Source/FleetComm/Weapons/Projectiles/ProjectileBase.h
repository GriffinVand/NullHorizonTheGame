#pragma once
#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectileBase.generated.h"

class UBoxComponent;

UCLASS(Blueprintable)
class FLEETCOMM_API AProjectileBase : public AActor
{
	GENERATED_BODY()
public:
	AProjectileBase();
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollision;
	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(EditAnywhere)
	float ProjectileSpeed = 1000;
	
};
