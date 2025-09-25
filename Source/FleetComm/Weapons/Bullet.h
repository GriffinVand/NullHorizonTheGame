#pragma once

#include "CoreMinimal.h"
#include "PoolableActor.h"
#include "Bullet.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class FLEETCOMM_API ABullet : public APoolableActor
{

	GENERATED_BODY()
public:

	ABullet();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet")
	USphereComponent* HitCollider;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet")
	UProjectileMovementComponent* ProjectileMovement;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void SetActive(const bool& IsActive) override;

protected:

	virtual void BeginPlay() override;
	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;


	
};
