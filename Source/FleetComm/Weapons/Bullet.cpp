
#include "Bullet.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ABullet::ABullet()
{
	HitCollider = CreateDefaultSubobject<USphereComponent>(TEXT("HitCollider"));
	HitCollider->InitSphereRadius(5.0f);
	HitCollider->BodyInstance.SetCollisionProfileName("Projectile");
	HitCollider->OnComponentHit.AddDynamic(this, &ABullet::OnHit);

	RootComponent = HitCollider;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = HitCollider;
	ProjectileMovement->InitialSpeed = 500.0f;
	ProjectileMovement->MaxSpeed = 500.0f;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
}


void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ReturnToPool();
}

void ABullet::FellOutOfWorld(const class UDamageType& dmgType)
{
	ReturnToPool();
}

void ABullet::SetActive(const bool& IsActive)
{
	Super::SetActive(IsActive);
	if (IsActive)
	{
		ProjectileMovement->Activate(true);
		ProjectileMovement->SetUpdatedComponent(RootComponent);
		ProjectileMovement->SetVelocityInLocalSpace(FVector().ForwardVector * ProjectileMovement->InitialSpeed);
	}
	
}



