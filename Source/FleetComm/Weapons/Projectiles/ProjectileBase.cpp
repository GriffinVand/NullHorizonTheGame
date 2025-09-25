#include "ProjectileBase.h"

#include "Components/BoxComponent.h"

AProjectileBase::AProjectileBase()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
	RootComponent = BoxCollision;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

}
