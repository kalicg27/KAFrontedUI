// RoadMap Komronbek Alimkulov - Allright 

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FrontedTypes/FrontendEnumTypes.h"

#include "FrontendUISybsystem.generated.h"

//Initialize the Class from other modules or headers
class UWidget_PrimaryLayout;
struct FGameplayTag;
class UWidget_ActivatableBase;
class UFrontendCommonButtonBase;

//ENum State
enum class EAsyncPushWidgetSlate : uint8
{
	OnCreatedBeforePush,
	AfterPush
};

// Multicast UE
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonDescriptionTextUpdatedDelegate, UFrontendCommonButtonBase*, BroadcastingButton, FText, DescriptionText);
/**
 * 
 */
UCLASS()
class KAFRONTEDUI_API UFrontendUISybsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

//Methods	
//UISybsystem
public:
	//WorldContextObject
	static UFrontendUISybsystem* Get(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable)
	void RegisterCreatedPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedWidget);

	void PushSoftWidgetToStackAnynsc(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<UWidget_ActivatableBase>InSoftWidgetClass, TFunction<void(EAsyncPushWidgetSlate, UWidget_ActivatableBase*)>AsyncPushStateCallback);
	void PushConfirmScreenToModalStackAsync(EConfirmScreenType InScreenType, const FText& InScreenTitle, const FText& InScreenMsg, TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallBack);

//UE
public:
	//From - USubsystem 
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	
//Properties
public:

	UPROPERTY(BlueprintAssignable)
	FOnButtonDescriptionTextUpdatedDelegate OnButtonDescriptionTextUpdated;
private:
	UPROPERTY(Transient)
	UWidget_PrimaryLayout* CreatedPrimaryLayout;

};
