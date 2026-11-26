// RoadMap Komronbek Alimkulov - Allright 
//Parent - UCommonUserWidget

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "FrontedTypes/FrontendEnumTypes.h"

#include "Widget_ListEntry_Base.generated.h"

//Forward Declarations
class UCommonTextBlock;
class UListDataObject_Base;


UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class KAFRONTEDUI_API UWidget_ListEntry_Base : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
//METHODS
public:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On List Entry Widget Hovered"))
	void BP_OnListEntryWidgetHovered(bool bWasHovered, bool bIsEntryWidgetStillSelected);
	void NativeOnListEntryWidgetHovered(bool bWasHovered);

protected:
	//the child widget blurptint should be able to override this function for the gamepad interaction to function correcty;
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName ="Get Widget To Focus For Gamepad"))
	UWidget* BP_GetWidgetToFocusForGamepad() const;

	//the child class could overtide this function to handle the initialization needed . super call is expeccted
	virtual void OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject);

	//the chid class could override this function to update the ui value after the object has been modified. Super call is no needed;
	virtual void OnOwningListDataObjectModified(UListDataObject_Base* OwningModifiedData, EOptionslistDataModifyReason ModifyReason);
	
	virtual void OnOwningDependencyDataObjectModified(UListDataObject_Base* OwningModifiedDependencyData, EOptionslistDataModifyReason ModifyReason);
	
	// the child class should override - super call is expected
	virtual void OnToggleEditableState(bool bIsEditable);

	void SelectThisEntryWidget();

//UE
protected:
	//from IUserObjectListEntry interface
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnEntryReleased() override;

	//from UUserWidget
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;


//BIND WIDGETS
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, AllowPrivateAccess = "true"))
	UCommonTextBlock* CommonText_SettingDisplayName;
	UPROPERTY(Transient)
	UListDataObject_Base* CachedOwningDataObject;
};
