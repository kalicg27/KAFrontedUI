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

//CHILD CLASSES

UCLASS()
class KAFRONTEDUI_API UListDataObject_StringBool : public UListDataObject_String
{
	GENERATED_BODY()

//METHODS
private:
	void TryInitBoolValues();

public:
	void OverrideTrueDisplayText(const FText& InNewTrueDisplayText);
	void OverrideFalseDisplayText(const FText& InNewFalseDisplayText);

	void SetTrueAsDefaultValue();
	void SetFalseAsDefaultValue();

//UE
protected:
	//from UListDataObject_String 
	virtual void OnDataObjectInitialized() override;

//PROPERTIES
private:
	const FString TrueString = TEXT("true");
	const FString FalseString = TEXT("false");

};

UCLASS()
class KAFRONTEDUI_API UListDataObject_StringEnum : public UListDataObject_String
{
	GENERATED_BODY()

//PROPERTIES
public:
	template<typename EnumType> 
	void AddEnumOptions(EnumType InEnumOption, const FText& InDisplayText)
	{
		const UEnum* StaticEnumOption = StaticEnum<EnumType>();
		const FString ConvertedEnumString = StaticEnumOption->GetNameStringByValue(InEnumOption);

		AddDynamicOption(ConvertedEnumString, InDisplayText);
	}

	template<typename EnumType>
	EnumType GetCurrentValueAsEnum() const
	{
		const UEnum* StaticEnumOption = StaticEnum<EnumType>();
		return (EnumType)StaticEnumOption->GetValueByNameString(CurrentStringValue);
	
	}

	template<typename EnumType>
	void SetDefaultValueFromEnumOption(EnumType InEnumOption)
	{
		const UEnum* StaticEnumOption = StaticEnum<EnumType>();
		const FString ConvertedEnumString = StaticEnumOption->GetNameStringByValue(InEnumOption);
	}
};