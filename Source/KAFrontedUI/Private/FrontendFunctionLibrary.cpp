// RoadMap Komronbek Alimkulov - Allright 


#include "FrontendFunctionLibrary.h"
#include "FrontendSettings/KAFrontendSettings.h"


TSoftClassPtr<UWidget_ActivatableBase> UFrontendFunctionLibrary::GetFrontendSoftWidgetClassByTag(UPARAM(meta = (Categories = "Frontend.Widget")) FGameplayTag InWidgetTag)
{
	const UKAFrontendSettings* FrontendDeveloperSettings = GetDefault<UKAFrontendSettings>();
	
	checkf(FrontendDeveloperSettings->FrontendWidgetMap.Contains(InWidgetTag), TEXT("Could not find corresponding widget bro under tag %s"), *InWidgetTag.ToString());

	return FrontendDeveloperSettings->FrontendWidgetMap.FindRef(InWidgetTag);


}
