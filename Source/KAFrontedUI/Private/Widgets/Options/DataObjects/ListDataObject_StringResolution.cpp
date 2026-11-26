// RoadMap Komronbek Alimkulov - Allright 


#include "Widgets/Options/DataObjects/ListDataObject_StringResolution.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widgets/Options/OptionsDataInteractionHelper.h"
#include "FrontendSettings/FrontendGameUserSettings.h"

#include "FrontendDebugHelper.h"

void UListDataObject_StringResolution::InitResolutionValues()
{
	TArray<FIntPoint> AvaiableResolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(AvaiableResolutions);

	AvaiableResolutions.Sort(
		[](const FIntPoint& A, const FIntPoint& B)->bool
		{
			return A.SizeSquared() < B.SizeSquared();
		}
	);
	for (const FIntPoint& Resolution : AvaiableResolutions)
	{
		//Avaialbe Resolution : X = 2560 Y = 1440
		//Avaialbe Resolution : X = 1920 Y = 1080
		//Avaialbe Resolution : X = 1280 Y = 720
		//Debug::Print(TEXT("Avaialbe Resolution : ") + Resolution.ToString());

		AddDynamicOption(ResToValueString(Resolution), ResToDisplayText(Resolution));
	}
	MaximumAllowedResolution = ResToValueString(AvaiableResolutions.Last());
	SetDefaultValueFromString(MaximumAllowedResolution);
}

void UListDataObject_StringResolution::OnDataObjectInitialized()
{
	Super::OnDataObjectInitialized();
	//if (DataDynamicGetter)
	//{
	//	Debug::Print(TEXT("Resolution value from dynamic gettter : ") + DataDynamicGetter->GetValueAsString());
	//	
	//}
	if(!TrySetDisplayTextFromStringValue(CurrentStringValue))
	{
		CurrentDisplayText = ResToDisplayText(UFrontendGameUserSettings::Get()->GetScreenResolution());
	}

}

FString UListDataObject_StringResolution::ResToValueString(const FIntPoint& InResolution) const
{
	return FString::Printf(TEXT("(X=%i,Y=%i)"), InResolution.X, InResolution.Y);
}

FText UListDataObject_StringResolution::ResToDisplayText(const FIntPoint& InResolution) const
{
	const FString DisplayString = FString::Printf(TEXT("%i x %i"), InResolution.X, InResolution.Y);
	return FText::FromString(DisplayString);
}
