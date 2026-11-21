// RoadMap Komronbek Alimkulov - Allright 
//Parent - UListDataObject_Base

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/DataObjects/ListDataObject_Base.h"

#include "ListDataObject_Value.generated.h"

//Forward Declarations
class FOptionsDataInteractionHelper;


UCLASS(Abstract)
class KAFRONTEDUI_API UListDataObject_Value : public UListDataObject_Base
{
	GENERATED_BODY()

//METHODS
public:
	void SetDataDynamicGetter(const TSharedPtr<FOptionsDataInteractionHelper>& InDynamicGetter);
	void SetDataDynamicSetter(const TSharedPtr<FOptionsDataInteractionHelper>& InDynamicSetter);

	//inline functions : 
	void SetDefaultValueFromString(const FString& InDefaultValue) { DefaultStringValue = InDefaultValue; }
	virtual bool HasDefaultValue()  const override { return DefaultStringValue.IsSet(); }

protected:
	FString GetDefaultValuesAsString() const { return DefaultStringValue.GetValue(); }

//PROPERTIES
protected:
	TSharedPtr<FOptionsDataInteractionHelper> DataDynamicGetter;
	TSharedPtr<FOptionsDataInteractionHelper> DataDynamicSetter;
private:
	TOptional<FString> DefaultStringValue;
};
