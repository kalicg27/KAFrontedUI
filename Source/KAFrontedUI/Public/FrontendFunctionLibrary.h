// RoadMap Komronbek Alimkulov - Allright 
//Parent - UBlueprintFunctionLibrary
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"

#include "FrontendFunctionLibrary.generated.h"

//Forward Declarations
class UWidget_ActivatableBase;

UCLASS()
class KAFRONTEDUI_API UFrontendFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
//METHODS
//FrontendFunctionLibrary - base
public:
	UFUNCTION(BlueprintPure, Category="Frontend Function Library")
	static TSoftClassPtr< UWidget_ActivatableBase> GetFrontendSoftWidgetClassByTag(UPARAM(meta = (Categories = "Frontend.Widget")) FGameplayTag InWidgetTag);

	UFUNCTION(BlueprintPure, Category = "Frontend Function Library")
	static TSoftObjectPtr<UTexture2D> GetOptionsSoftImageByTag(UPARAM(meta = (Categories = "Frontend.Image")) FGameplayTag InImageTag);
};
