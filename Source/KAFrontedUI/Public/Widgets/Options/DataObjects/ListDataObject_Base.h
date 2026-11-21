// RoadMap Komronbek Alimkulov - Allright 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FrontedTypes/FrontendEnumTypes.h"
#include "ListDataObject_Base.generated.h"
 
#define LIST_DATA_ACCESSOR(DataType,PropertyName) \
	FORCEINLINE DataType Get##PropertyName() const {return PropertyName;}\
	void Set##PropertyName(DataType In##PropertyName) {PropertyName = In##PropertyName;}

/**
 * 
 */
UCLASS(Abstract)
class KAFRONTEDUI_API UListDataObject_Base : public UObject
{
	GENERATED_BODY()
	

public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnListDataModifiedDelegate, UListDataObject_Base*,EOptionslistDataModifyReason )
	FOnListDataModifiedDelegate OnListDataModified;


	//FORCEINLINE FName GetDataID() const { return DataID; }
	//void SetDataID(FName InDataID) { DataID = InDataID; }
	LIST_DATA_ACCESSOR(FName, DataID)
		LIST_DATA_ACCESSOR(FText, DataDisplayName)
		LIST_DATA_ACCESSOR(FText, DescrtiptionRichText)
		LIST_DATA_ACCESSOR(FText, DisabledRichText)
		LIST_DATA_ACCESSOR(TSoftObjectPtr<UTexture2D>, SoftDecriptionImage)
		LIST_DATA_ACCESSOR(UListDataObject_Base*, ParentData)


	void InitDataObject();

	//empty in the base class . Child clasas ListDataBoject_Collection should overrite it , the fuctnion should return all the child data  a tab has
	virtual TArray<UListDataObject_Base*> GetAllChildListData() const {return TArray< UListDataObject_Base*>();}
	virtual bool HasAnyChildListData() const { return false;}

	void SetShouldApplySettingsImmediately(bool bShouldApplyRightAway) { bShouldApplyChangeImmediatly = bShouldApplyRightAway; }

	//the child class should override them to provide implementations for resetting the data!
	virtual bool HasDefaultValue()  const { return false; }
	virtual bool CanResetBackToDefaultValue() const { return false; }
	virtual bool TryResetBackToDefaultValue()  { return false; }
protected:
	//empty in base class,, the child classes should override it to handle the initilazed neede accordingly;
	virtual void OnDataObjectInitialized(); 

	virtual void NotifyListDataModified(UListDataObject_Base* ModifiedData, EOptionslistDataModifyReason ModifyReason = EOptionslistDataModifyReason::DirectlyModified);
private:
	FName DataID;
	FText DataDisplayName;
	FText DescrtiptionRichText;
	FText DisabledRichText;
	TSoftObjectPtr<UTexture2D> SoftDecriptionImage;

	UPROPERTY(Transient)
	UListDataObject_Base* ParentData;

	bool bShouldApplyChangeImmediatly = false;
};
