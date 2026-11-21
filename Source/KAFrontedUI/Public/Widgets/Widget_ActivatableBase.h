// RoadMap Komronbek Alimkulov - Allright 

//Parent - UCommonActivatableWidget
#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"

#include "Widget_ActivatableBase.generated.h"

// Forward Declarations
class AFrontedUIPlayerController;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class KAFRONTEDUI_API UWidget_ActivatableBase : public UCommonActivatableWidget
{
	GENERATED_BODY()

//METHODS
 
//Widget_ActivatableBase
protected:
	UFUNCTION(BlueprintPure)
	AFrontedUIPlayerController* GetOwningFrontendUIPlayerController();

//PROPERTIES 
private:
	TWeakObjectPtr<AFrontedUIPlayerController> CachedOwningFrontendPC;

};
