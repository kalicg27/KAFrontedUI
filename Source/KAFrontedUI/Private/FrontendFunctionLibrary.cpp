// RoadMap Komronbek Alimkulov - Allright 

#include "FrontendFunctionLibrary.h"

#include "FrontendSettings/KAFrontendSettings.h"

//FrontendFunctionLibrary - base
TSoftClassPtr<UWidget_ActivatableBase> UFrontendFunctionLibrary::GetFrontendSoftWidgetClassByTag(UPARAM(meta = (Categories = "Frontend.Widget")) FGameplayTag InWidgetTag)
{
	const UKAFrontendSettings* FrontendDeveloperSettings = GetDefault<UKAFrontendSettings>();
	
	checkf(FrontendDeveloperSettings->FrontendWidgetMap.Contains(InWidgetTag), TEXT("Could not find corresponding widget bro under tag %s"), *InWidgetTag.ToString());

	return FrontendDeveloperSettings->FrontendWidgetMap.FindRef(InWidgetTag);

}

TSoftObjectPtr<UTexture2D> UFrontendFunctionLibrary::GetOptionsSoftImageByTag(FGameplayTag InImageTag)
{
	const UKAFrontendSettings* FrontendDeveloperSettings = GetDefault<UKAFrontendSettings>();
	checkf(FrontendDeveloperSettings->OptionsScreenSoftImageMap.Contains(InImageTag), TEXT("could not find image bro , please choose valid tag, your tag that failed is %s"), *InImageTag.ToString());
	return FrontendDeveloperSettings->OptionsScreenSoftImageMap.FindRef(InImageTag);

}