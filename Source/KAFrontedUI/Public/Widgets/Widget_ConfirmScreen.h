// RoadMap Komronbek Alimkulov - Allright 
//Parent - UObject

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "FrontedTypes/FrontendEnumTypes.h"

#include "Widget_ConfirmScreen.generated.h"

//Forward Declarations
class UCommonTextBlock;
class UDynamicEntryBox;

//STRUCTS
USTRUCT(BlueprintType)
struct FConfirmScreenButtonInfo
{
	GENERATED_BODY()

//PROPERTIES
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EConfirmScreenButtonType ConfirmScreenButtonType = EConfirmScreenButtonType::Unknown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ButtonTextDisplay;

};

// ConfirmScreenInfoObject (Data Object)
UCLASS()
class KAFRONTEDUI_API UConfirmScreenInfoObject : public UObject
{
	GENERATED_BODY()

//METHODS
	//ConfirmScreenInfoObject
public:
	static UConfirmScreenInfoObject* CreateOKScreen(const FText& InScreenTtle, const FText& InScreenMsg);
	static UConfirmScreenInfoObject* CreateYesNoScreen(const FText& InScreenTtle, const FText& InScreenMsg);
	static UConfirmScreenInfoObject* CreateOkCanselScreen(const FText& InScreenTtle, const FText& InScreenMsg);

//PROPERTIES
public:
	UPROPERTY(Transient)
	FText ScreenTitle;

	UPROPERTY(Transient)
	FText ScreenMessage;

	UPROPERTY(Transient)
	TArray< FConfirmScreenButtonInfo> AvailableScreenButtons;

};

//Widget Confirmatin Screen , Main widget
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class KAFRONTEDUI_API UWidget_ConfirmScreen : public UWidget_ActivatableBase
{
	GENERATED_BODY()

//METHODS
//Widget Confirmatin Screen
public:
	//gets called outside of the class when this wiget is contrusted and dbefore pushed

	void InitConfirmScreen(UConfirmScreenInfoObject* InScreenInfoObject, TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallback);

//PROPERTIES
private:
	UPROPERTY(meta = (BindWidget))
	UCommonTextBlock* CommonTextBlock_Title;

	UPROPERTY(meta = (BindWidget))
	UCommonTextBlock* CommonTextBlock_Message;

	UPROPERTY(meta = (BindWidget))
	UDynamicEntryBox* DynamicEntryBox_Buttons;
};
