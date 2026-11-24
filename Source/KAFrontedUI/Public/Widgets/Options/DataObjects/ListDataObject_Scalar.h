// RoadMap Komronbek Alimkulov - Allright 

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/DataObjects/ListDataObject_Value.h"
#include "CommonNumericTextBlock.h"

#include "ListDataObject_Scalar.generated.h"

/**
 * 
 */
UCLASS()
class KAFRONTEDUI_API UListDataObject_Scalar : public UListDataObject_Value
{
	GENERATED_BODY()

//METHODS
//ListDataObject_Scalar
public:
	LIST_DATA_ACCESSOR(TRange<float>, DisplayValueRange)
		LIST_DATA_ACCESSOR(TRange<float>, OutputValueRange)
		LIST_DATA_ACCESSOR(float, SliderStepSize)
		LIST_DATA_ACCESSOR(ECommonNumericType, DisplayNumericType)
		LIST_DATA_ACCESSOR(FCommonNumberFormattingOptions, NumberFormattingOptions)

	static FCommonNumberFormattingOptions NoDecimal();
	static FCommonNumberFormattingOptions WithDecimal(int32 NumFracDigit);

	float GetCurrentValue() const;
	void SetCurrentValueFromSlider(float InNewValue);

private:
	float StringToFloat(const FString& InString) const;

//UListDataObject_Base
protected:
	virtual bool CanResetBackToDefaultValue() const override;
	virtual bool TryResetBackToDefaultValue()  override;

//PROPERTIES
private:
	TRange<float> DisplayValueRange = TRange<float>(0.f, 1.f);
	TRange<float> OutputValueRange = TRange<float>(0.f, 1.f);
	float SliderStepSize = 0.1f;
	ECommonNumericType DisplayNumericType = ECommonNumericType::Number;
	FCommonNumberFormattingOptions NumberFormattingOptions;

	
};
