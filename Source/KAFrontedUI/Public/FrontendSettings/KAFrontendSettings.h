// RoadMap Komronbek Alimkulov - Allright 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"

#include "KAFrontendSettings.generated.h"
class UWidget_ActivatableBase;
/**
 * 
 */
UCLASS(Config = Game,defaultconfig, meta =(DisplayName= "KA Frontend UI Settings"))
class KAFRONTEDUI_API UKAFrontendSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(Config, EditAnywhere, Category = "Widget Reference", meta = (Categories = "Frontend.Widget"))
	TMap<FGameplayTag, TSoftClassPtr<UWidget_ActivatableBase>> FrontendWidgetMap;

};
