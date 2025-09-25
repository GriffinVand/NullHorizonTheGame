#include "TargetFinderComponent.h"

#include "Chaos/Utilities.h"
#include "FleetComm/Weapons/WeaponTesting/TestDummy.h"
#include "Kismet/GameplayStatics.h"

void UTargetFinderComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTargetFinderComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTargetFinderComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

bool UTargetFinderComponent::IsTargetValid(ATestDummy* Target)
{
	if (Target)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(CameraLocation, CameraRotation);
		FVector CameraForward = CameraRotation.Vector();
		FVector ToDummy = Target->GetActorLocation() - CameraLocation;
		float Dot = FVector::DotProduct(ToDummy, CameraForward);
		return (Dot >= 0.7);
	}
	return false;
}

ATestDummy* UTargetFinderComponent::GetTarget()
{
	FVector CameraLocation;
	FRotator CameraRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(CameraLocation, CameraRotation);
	FVector CameraForward = CameraRotation.Vector();
	TArray<AActor*> PossibleTargets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATestDummy::StaticClass(), PossibleTargets);
	ATestDummy* BestTarget = nullptr;
	float BestDot = -1;
	for (auto& Target : PossibleTargets)
	{
		if (ATestDummy* TestDummy = Cast<ATestDummy>(Target))
		{
			FVector ToDummy = TestDummy->GetActorLocation() - CameraLocation;
			float Dot = FVector::DotProduct(ToDummy, CameraForward);
			if (Dot > BestDot && Dot >= 0.7) 
			{
				//TODO: Add line trace
				BestTarget = TestDummy;
			}
		}
	}
	return BestTarget;
}





