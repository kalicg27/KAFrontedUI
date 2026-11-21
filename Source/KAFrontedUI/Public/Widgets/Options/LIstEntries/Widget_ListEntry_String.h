// RoadMap Komronbek Alimkulov - Allright 
//Parent - UWidget_ListEntry_Base

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/LIstEntries/Widget_ListEntry_Base.h"

#include "Widget_ListEntry_String.generated.h"

//Forward Declarations
class UFrontendCommonButtonBase;
class UFrontendCommonRotator;
class UListDataObject_String;


UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class KAFRONTEDUI_API UWidget_ListEntry_String : public UWidget_ListEntry_Base
{
	GENERATED_BODY()

//METHODS
//Widget_ListEntry_String
private:
	void OnPreviousOptionButtonClicked();
	void OnNextOptionButtonClicked();

	void OnRotatorValueChanged(int32 Value, bool bUserInitiated);

//UListDataObject_Base
protected:
	virtual void OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject) override;
	virtual void OnOwningListDataObjectModified(UListDataObject_Base* OwningModifiedData, EOptionslistDataModifyReason ModifyReason) override;

//UE
protected:
	//From UUserWidget
	virtual void NativeOnInitialized() override;


//BIND WIDGETS
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UFrontendCommonButtonBase* CommonButton_PreviousOption;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UFrontendCommonRotator* CommonRotator_AvailableOptions;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UFrontendCommonButtonBase* CommonButton_NextOption;
	
//PROPERTIES
private:
	UPROPERTY(Transient)
	UListDataObject_String* CachedOwningStringDataObject;

};
