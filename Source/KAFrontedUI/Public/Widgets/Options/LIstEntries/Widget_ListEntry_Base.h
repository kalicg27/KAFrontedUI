// RoadMap Komronbek Alimkulov - Allright 

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "FrontedTypes/FrontendEnumTypes.h"


#include "Widget_ListEntry_Base.generated.h"

class UCommonTextBlock;
class UListDataObject_Base;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DistableNativeTick))
class KAFRONTEDUI_API UWidget_ListEntry_Base : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On List Entry Widget Hovered"))
	void BP_OnListEntryWidgetHovered(bool bWasHovered, bool bIsEntryWidgetStillSelected);
	void NativeOnListEntryWidgetHovered(bool bWasHovered);

protected:
	//-begin from IUserObjectListEntry interface
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	//the child class whoulsd overtide this function to handle the initialization needed . super call is expeccted
	virtual void OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject);

	//the chid class houdl override this function to updat the ui value after the object has been modified. Super call is no needed;
	virtual void OnOwningListDataObjectModified(UListDataObject_Base* OwningModifiedData, EOptionslistDataModifyReason ModifyReason);

	void SelectThisEntryWidget();
private:
	//bound widgets
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, AllowPrivateAccess = "true"))
	UCommonTextBlock* CommonText_SettingDisplayName;
	//bound widgets

	
};
