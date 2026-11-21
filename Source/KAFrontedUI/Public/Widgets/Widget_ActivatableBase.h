// RoadMap Komronbek Alimkulov - Allright 

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Widget_ActivatableBase.generated.h"

class AFrontedUIPlayerController;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DistableNativeTick))
class KAFRONTEDUI_API UWidget_ActivatableBase : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintPure)
	AFrontedUIPlayerController* GetOwningFrontendUIPlayerController();
private:
	TWeakObjectPtr<AFrontedUIPlayerController> CachedOwningFrontendPC;
};
