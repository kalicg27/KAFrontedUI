// RoadMap Komronbek Alimkulov - Allright 
//This is Developer Settings 
// Parent - UDeveloperSettings
#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"

#include "KAFrontendSettings.generated.h"

// Forward Declarations
class UWidget_ActivatableBase;

UCLASS(Config = Game,defaultconfig, meta =(DisplayName= "KA Frontend UI Settings"))
class KAFRONTEDUI_API UKAFrontendSettings : public UDeveloperSettings
{
	GENERATED_BODY()

//PROPERTIES
//KAFrontendSettings
public:
	UPROPERTY(Config, EditAnywhere, Category = "Widget Reference", meta = (Categories = "Frontend.Widget"))
	TMap<FGameplayTag, TSoftClassPtr<UWidget_ActivatableBase>> FrontendWidgetMap;

	UPROPERTY(Config, EditAnywhere, Category = "Options Image Reference", meta = (Categories = "Frontend.Image"))
	TMap< FGameplayTag, TSoftObjectPtr<UTexture2D>> OptionsScreenSoftImageMap;

};
