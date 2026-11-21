// RoadMap Komronbek Alimkulov - Allright 
//Parent - UBlueprintAsyncActionBase

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FrontedTypes/FrontendEnumTypes.h"

#include "AsyncAction_PushConfirmScreen.generated.h"

//DELEGATES
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConfirmScreenButtonClickedDelate, EConfirmScreenButtonType, ClickedButtonType);


UCLASS()
class KAFRONTEDUI_API UAsyncAction_PushConfirmScreen : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

//METHODS

//AsyncAction - PushConfirmScreen
public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject", BlueprintInternalUseOnly = "true", DisplayName = "Show Confirmation Screen"))
	static UAsyncAction_PushConfirmScreen* PushConfirmScreen(
		const UObject* WorldContextObject,
		EConfirmScreenType ScreenType,
		FText InScreenTitle,
		FText InScreenMessage
	);

//UE
public:
	//from UBlueprintAsyncActionBase
	virtual void Activate() override;

//PROPERTIES
//AsyncAction - PushConfirmScreen
public:
	UPROPERTY(BlueprintAssignable) 
	FOnConfirmScreenButtonClickedDelate OnButtonClicked;
private:
	TWeakObjectPtr<UWorld> CachedOwningWorld;
	EConfirmScreenType CachedScreenType;
	FText CachedScreenTitle;
	FText CachedScreenMessage;

};
