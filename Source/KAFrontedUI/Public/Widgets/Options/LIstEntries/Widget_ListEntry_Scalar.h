// RoadMap Komronbek Alimkulov - Allright 
//Parent - UWidget_ListEntry_Base

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/LIstEntries/Widget_ListEntry_Base.h"
#include "Widget_ListEntry_Scalar.generated.h"

//Forward Declarations
class UCommonNumericTextBlock;
class UAnalogSlider;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class KAFRONTEDUI_API UWidget_ListEntry_Scalar : public UWidget_ListEntry_Base
{
	GENERATED_BODY()

//METHODS

//Widget_ListEntry_String


//UListDataObject_Base
protected:
	virtual void OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject) override;
	virtual void OnOwningListDataObjectModified(UListDataObject_Base* OwningModifiedData, EOptionslistDataModifyReason ModifyReason) override;

//UE
protected:
	//From UUserWidget
	virtual void NativeOnInitialized() override;

//BOUND WIDGETS
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UCommonNumericTextBlock* CommonNumeric_SettingValue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UAnalogSlider* AnalogSlider_SettingSlider;
	
};
