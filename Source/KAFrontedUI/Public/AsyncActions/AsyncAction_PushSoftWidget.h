// RoadMap Komronbek Alimkulov - Allright 
 
//Parent - UBlueprintAsyncActionBase
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GameplayTagContainer.h"

#include "AsyncAction_PushSoftWidget.generated.h"

// Forward Declarations
class UWidget_ActivatableBase;

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPushSoftWidgetDelagete, UWidget_ActivatableBase*, PushedWidget);

UCLASS()
class KAFRONTEDUI_API UAsyncAction_PushSoftWidget : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
//METHODS
//AsyncAction_PushSoftWidget
public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject", BlueprintInternalUseOnly = "true", DisplayName = "Push Soft Widget to Widget Stack"))
	static UAsyncAction_PushSoftWidget* PushSoftWidget(const UObject* WorldContextObject,
		APlayerController* OwningPlayerController, TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
		UPARAM(meta = (Categories = "Frontend.WidgetStack")) FGameplayTag InWidgetStackTag,
		bool bFocusOnNewlyPushedWidget = true);

//UE
public:
	//from UBlueprintAsyncActionBase
	virtual void Activate() override;

//PROPERTIES
public:
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
