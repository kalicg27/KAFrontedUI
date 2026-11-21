// RoadMap Komronbek Alimkulov - Allright 
//Parent - UListDataObject_Value

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/DataObjects/ListDataObject_Value.h"

#include "ListDataObject_String.generated.h"


UCLASS()
class KAFRONTEDUI_API UListDataObject_String : public UListDataObject_Value
{
	GENERATED_BODY()
	
//METHODS
//ListDataObject_String
public:
	void AddDynamicOption(const FString& InStringValue, const FText& InDisplayText);
	void AdvanceToNextOption();
	void BackToPreviousOption();
	void OnRotatorInitiatedValueChange(const FText& InNewSelectedText);

	FORCEINLINE const TArray<FText>& GetAvailableOptionsTextArray() const { return AvaialableOptionsTextArray; }
	FORCEINLINE FText GetCurrentDisplayText() const { return CurrentDisplayText; }

protected:
	bool TrySetDisplayTextFromStringValue(const FString& InStringValue);

//UListDataObject_Base
protected:
	virtual void OnDataObjectInitialized() override;
	virtual bool CanResetBackToDefaultValue() const override;
	virtual bool TryResetBackToDefaultValue()  override;

//PROPERTIES
protected:
	FString CurrentStringValue;
	FText CurrentDisplayText;
	TArray<FString> AvailableOptionsStringArray;
	TArray<FText> AvaialableOptionsTextArray;
	
	
};
