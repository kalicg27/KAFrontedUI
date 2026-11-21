// RoadMap Komronbek Alimkulov - Allright 

#pragma once

#include "CoreMinimal.h"
#include "PropertyPathHelpers.h"

//Forward Declarations
class UFrontendGameUserSettings;

class KAFRONTEDUI_API FOptionsDataInteractionHelper
{

//METHODS
//OptionsData_InteractionHelper
public:
	FOptionsDataInteractionHelper(const FString& InSetterOrGetterFuncPath);

	FString GetValueAsString() const;
	void SetValueFromString(const FString& InStringValue);

//PROPERTIES
private:
	FCachedPropertyPath CachedDynamicFunctionPath;

	TWeakObjectPtr< UFrontendGameUserSettings> CachedWeakGameUserSettings;
};
