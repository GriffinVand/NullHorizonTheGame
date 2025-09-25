#pragma once
#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "FleetComm/Weapons/WeaponData/WeaponDefinition.h"
#include "WeaponComponent.generated.h"

class UWeaponFireBehavior;
class UWeaponDefinition;
class UWeaponFireType;
class UTargetFinderComponent;

UENUM(BlueprintType)
enum class EWeaponSlot : uint8
{
	Primary UMETA(DisplayName = "Primary"),
	Secondary UMETA(DisplayName = "Secondary"),
};

USTRUCT(BlueprintType)
struct FFireTransform
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bValidTransform = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Origin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator Direction;
};
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FLEETCOMM_API UWeaponComponent : public USceneComponent
{
	GENERATED_BODY()
public:

	bool bProper = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* WeaponUIWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* BulletSpawnPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponDefinition* WeaponDefinition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponFireBehavior* WeaponFireBehavior;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponFireType* WeaponFireType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponMeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTargetFinderComponent* TargetFinderComp;

	UWeaponComponent();
	
	void OnActivate();
	void OnDeactivate();
	
	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
	virtual void OnRegister() override;
	
	void UpdateUI();
	void InitializeFireBehavior();
	void InitializeFireType();
	FFireTransform GetFireTransform();
	UFUNCTION(BlueprintCallable)
	void FirePressed();
	UFUNCTION(BlueprintCallable)
	void FireReleased();
};
