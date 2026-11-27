// RoadMap Komronbek Alimkulov - Allright 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "KAFrontendLoadScreenSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig)
class KAFRONTEDUI_API UKAFrontendLoadScreenSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
//METHODS
public:
	TSubclassOf<UUserWidget> GetLoadingScreenWidgetClassChecked() const;

//PROPERTIES
public:

	UPROPERTY(Config, EditAnywhere, Category = "Loading Screen Settings")
	TSoftClassPtr<UUserWidget> SoftloadingScreenWidgetClass;

	UPROPERTY(Config, EditAnywhere, Category = "Loading Screen Settings")
	float HoldLoadingScreenExtraSeconds = 10.f;

	UPROPERTY(Config, EditAnywhere, Category = "Loading Screen Settings")
	bool bShouldLoadingScreenInEditor = false;


};
