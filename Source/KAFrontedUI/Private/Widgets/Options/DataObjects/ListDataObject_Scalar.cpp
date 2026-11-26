// RoadMap Komronbek Alimkulov - Allright 


#include "Widgets/Options/DataObjects/ListDataObject_Scalar.h"
#include "Widgets/Options/OptionsDataInteractionHelper.h"

FCommonNumberFormattingOptions UListDataObject_Scalar::NoDecimal()
{
	FCommonNumberFormattingOptions Options;
	Options.MaximumFractionalDigits = 0;
	return Options;
}

FCommonNumberFormattingOptions UListDataObject_Scalar::WithDecimal(int32 NumFracDigit)
{
	FCommonNumberFormattingOptions Options;
	Options.MaximumFractionalDigits = NumFracDigit;
	return Options;
}

float UListDataObject_Scalar::GetCurrentValue() const
{
	if (DataDynamicGetter)
	{
		return FMath::GetMappedRangeValueClamped(
			OutputValueRange,
			DisplayValueRange,
			StringToFloat(DataDynamicGetter->GetValueAsString())
		);
	}
	return 0.0f;
}

void UListDataObject_Scalar::SetCurrentValueFromSlider(float InNewValue)
{
	if (DataDynamicSetter)
	{
		const float ClampedValue = FMath::GetMappedRangeValueClamped(
			DisplayValueRange,
			OutputValueRange,
			InNewValue
		);
		DataDynamicSetter->SetValueFromString(LexToString(ClampedValue));
		NotifyListDataModified(this);
	}
}

float UListDataObject_Scalar::StringToFloat(const FString& InString) const
{
	float OutConvertedValue = 0.f;

	LexFromString(OutConvertedValue, InString);
	return OutConvertedValue;
}

//UListDataObject_Base
bool UListDataObject_Scalar::CanResetBackToDefaultValue() const
{
	if (HasDefaultValue() &&DataDynamicGetter)
	{
		const float DefaultValue = StringToFloat(GetDefaultValuesAsString());
		const float CurrentValue = StringToFloat(DataDynamicGetter->GetValueAsString());
		
		return !FMath::IsNearlyEqual(DefaultValue, CurrentValue, 0.01f);
	}
	return false;
}

bool UListDataObject_Scalar::TryResetBackToDefaultValue()
{
	if (CanResetBackToDefaultValue())
	{
		if (DataDynamicGetter)
		{
			//const FString& AnotherString = GetDefaultValuesAsString();
			DataDynamicSetter->SetValueFromString(GetDefaultValuesAsString());

			NotifyListDataModified(this, EOptionslistDataModifyReason::ResetToDefault);
			//const FString& CurrentValueee = DataDynamicGetter->SetValueFromString();

			return true;
		}
	}
	return false;
}

void UListDataObject_Scalar::OnEditDependencyDataModified(UListDataObject_Base* ModifiedDependencyData, EOptionslistDataModifyReason ModifyReason)
{
	NotifyListDataModified(this, EOptionslistDataModifyReason::DependencyModified);
	Super::OnEditDependencyDataModified(ModifiedDependencyData, ModifyReason);
}
