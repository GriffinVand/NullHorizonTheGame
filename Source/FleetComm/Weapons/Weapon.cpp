// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "ObjectPool.h"
#include "FleetComm/FleetCommGameMode.h"
#include "GameFramework/GameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UWeapon::UWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	PrimarySkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMesh"));
	BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSpawnPoint"));
	// ...
}


// Called when the game starts
void UWeapon::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MaxAmmo;
	// ...
	GameMode = Cast<AFleetCommGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}


// Called every frame
void UWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UWeapon::FireWeapon()
{
	if (CurrentAmmo <= 0 || !ReadyToFire) return false;

	//Start fire rate timer
	ReadyToFire = false;
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() { ReadyToFire = true; }, FireRate, false);
	
	GetBullet();
	CurrentAmmo--;
	
	return true;
}

void UWeapon::GetBullet()
{
	APoolableActor* Bullet = GameMode->TestBulletPool->RetrievePooledObject(BulletSpawnPoint->GetComponentLocation(), BulletSpawnPoint->GetComponentRotation());
}


