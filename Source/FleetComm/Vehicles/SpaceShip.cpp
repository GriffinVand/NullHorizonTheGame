// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"
#include "EnhancedInputComponent.h"
#include "ShipMovementManager.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "FleetComm/Weapons/Weapon.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ASpaceShip::ASpaceShip()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMesh;
	ShipMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ShipMesh->SetSimulatePhysics(true);
	ShipMesh->SetEnableGravity(false);

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);

	//CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	//RootComponent = CapsuleCollider;
	
	ShipMovementManager = CreateDefaultSubobject<UShipMovementManager>(TEXT("ShipMovement"));
	ShipMovementManager->UpdatedComponent = ShipMesh;

	PrimaryWeapon = CreateDefaultSubobject<UWeapon>(TEXT("PrimaryWeapon"));
	PrimaryWeapon->SetupAttachment(RootComponent);
	PrimaryWeapon->PrimarySkeletalMesh->SetupAttachment(PrimaryWeapon);
	PrimaryWeapon->BulletSpawnPoint->SetupAttachment(PrimaryWeapon);

	SecondaryWeapon = CreateDefaultSubobject<UWeapon>(TEXT("SecondaryWeapon"));
	SecondaryWeapon->SetupAttachment(RootComponent);
	SecondaryWeapon->PrimarySkeletalMesh->SetupAttachment(SecondaryWeapon);
	SecondaryWeapon->BulletSpawnPoint->SetupAttachment(SecondaryWeapon);
}

// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpaceShip::PossesShip(APlayerController* PlayerController)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Jumping
		InputBindings.Add(PitchRollAction, &EnhancedInputComponent->BindAction(PitchRollAction, ETriggerEvent::Triggered, ShipMovementManager, &UShipMovementManager::PitchRollByInput));
		InputBindings.Add(YawAction, &EnhancedInputComponent->BindAction(YawAction, ETriggerEvent::Triggered, ShipMovementManager, &UShipMovementManager::YawByInput));
		InputBindings.Add(AccelAction, &EnhancedInputComponent->BindAction(AccelAction, ETriggerEvent::Triggered, ShipMovementManager, &UShipMovementManager::AccelerateByInput));
		InputBindings.Add(DecelAction, &EnhancedInputComponent->BindAction(DecelAction, ETriggerEvent::Triggered, ShipMovementManager, &UShipMovementManager::DecelerateByInput));
		InputBindings.Add(DecelAction, &EnhancedInputComponent->BindAction(ToggleFlightMode, ETriggerEvent::Triggered, ShipMovementManager, &UShipMovementManager::ToggleFlightMode));
		
		InputBindings.Add(PrimaryFireAction, &EnhancedInputComponent->BindAction(PrimaryFireAction, ETriggerEvent::Triggered, this, &ASpaceShip::PrimaryFire));
		InputBindings.Add(SecondaryFireAction, &EnhancedInputComponent->BindAction(SecondaryFireAction, ETriggerEvent::Triggered, this, &ASpaceShip::SecondaryFire));

		InputBindings.Add(LookAction, &EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASpaceShip::Look));
		InputBindings.Add(ResetCamAction, &EnhancedInputComponent->BindAction(ResetCamAction, ETriggerEvent::Triggered, this, &ASpaceShip::ResetCam));

		InputBindings.Add(ToggleShipMenuAction, &EnhancedInputComponent->BindAction(ToggleShipMenuAction, ETriggerEvent::Triggered, this, &ASpaceShip::ToggleShipMenu));
	}
	else
	{
		//UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ASpaceShip::UnpossesShip()
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		for (auto& Pair : InputBindings)
		{
			EnhancedInputComponent->RemoveBinding(*(Pair.Value));
		}
	}
	if (ShipMenuWidget)
	{
		CloseMenu();
	}
}

void ASpaceShip::ToggleShipMenu()
{
	//if (!ShipMenuClass) return;
	if (ShipMenuWidget)
	{
		CloseMenu();
	}
	else
	{
		OpenMenu();
	}
}

void ASpaceShip::OpenMenu()
{
	ShipMenuWidget = CreateWidget(Cast<APlayerController>(GetController()), ShipMenuClass);
	ShipMenuWidget->AddToViewport();
}

void ASpaceShip::CloseMenu()
{
	ShipMenuWidget->RemoveFromParent();
	ShipMenuWidget = nullptr;
}

void ASpaceShip::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisValue = Value.Get<FVector2D>();
	float DeltaTime = GetWorld()->GetDeltaSeconds();

	// Get current rotation
	FRotator CurrentRotation = CameraArm->GetRelativeRotation();
	//Step input thresholds for half/full flick
	std::tuple<float, float> thresholds= std::make_tuple(0.4f, 0.85f);

	//Get controller input values
	float YawInput = LookAxisValue.X;
	float PitchInput = LookAxisValue.Y;
	
	float YawLockAmt = abs(YawInput) >= std::get<1>(thresholds) ? 90:35; //Yaw gets locked to half/full tilt based on input
	float PitchLockAmt = abs(PitchInput) >= std::get<1>(thresholds) ? 90:35; //Pitch gets locked to half/full tilt based on input


	//Checks whether yaw rotation should happen or not
	float TargetYaw = (abs(YawInput) >= std::get<0>(thresholds)) ?
	FMath::Clamp(CurrentRotation.Yaw + (int)((YawInput) * 90), -1*YawLockAmt, YawLockAmt) : 0.f; //If above threshold, rotate yaw

	//Checks whether pitch rotation should happen or not
	float TargetPitch = (abs(PitchInput) >= std::get<0>(thresholds)) ?
	FMath::Clamp(CurrentRotation.Pitch + (int)((PitchInput) * 90), -1*PitchLockAmt, PitchLockAmt) : 0.f; //If above threshold, rotate pitch

	FRotator TargetRotation(TargetPitch, TargetYaw, 0.f);
	//Lerp speed
	float LerpSpeed = 7.5f; 
	FRotator SmoothedRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, LerpSpeed);

	//Apply rotation
	CameraArm->SetRelativeRotation(SmoothedRotation);
}

void ASpaceShip::ResetCam(const FInputActionValue& Value)
{
	
	// float DeltaTime = GetWorld()->GetDeltaSeconds();
	//
	// FRotator CurrentRotation = CameraArm->GetRelativeRotation();
	// float InterpSpeed = 8.f;
	// float NewSmoothedYaw = FMath::FInterpTo(CurrentRotation.Yaw, 180,DeltaTime, InterpSpeed);
	// FRotator NewRotation (0,NewSmoothedYaw,0);
	CameraArm->SetRelativeRotation(FRotator(0,180,0));
	
}

void ASpaceShip::PrimaryFire(const FInputActionValue& Value)
{
	if (PrimaryWeapon && PrimaryWeapon->FireWeapon())
	{
		
	}
}
void ASpaceShip::SecondaryFire(const FInputActionValue& Value)
{
	if (SecondaryWeapon && SecondaryWeapon->FireWeapon())
	{
		
	}
}
