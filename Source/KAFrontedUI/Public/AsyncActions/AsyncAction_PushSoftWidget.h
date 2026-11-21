// RoadMap Komronbek Alimkulov - Allright 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GameplayTagContainer.h"

#include "AsyncAction_PushSoftWidget.generated.h"
class UWidget_ActivatableBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPushSoftWidgetDelagete, UWidget_ActivatableBase*, PushedWidget);
/**
 * 
 */
UCLASS()
class KAFRONTEDUI_API UAsyncAction_PushSoftWidget : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject", BlueprintInternalUseOnly = "true", DisplayName = "Push Soft Widget to Widget Stack"))
	static UAsyncAction_PushSoftWidget* PushSoftWidget(const UObject* WorldContextObject,
		APlayerController* OwningPlayerController, TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
		UPARAM(meta = (Categories = "Frontend.WidgetStack")) FGameplayTag InWidgetStackTag,
		bool bFocusOnNewlyPushedWidget = true);
	//Begin of UBlueprintAsyncActionBase interface
	virtual void Activate() override;
	//end of UBlueprintAsyncActionBase interface;

	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelagete OnWidgetCreatedBeforePush;

	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelagete AfterPush;

private:
	TWeakObjectPtr<UWorld> CashedOwningWorld;
	TWeakObjectPtr<APlayerController> CashedOwningPC;
	TSoftClassPtr<UWidget_ActivatableBase> CashedSoftWidgetClass;
	FGameplayTag CashedWidgetStackTag;
	bool bCashedbFocusOnNewlyPushedWidget = false;


	
};
