#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "LockOnIndicatorWidget.generated.h"

UCLASS(Blueprintable)
class FLEETCOMM_API ULockOnIndicatorWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UImage* LockImage;
	
};
