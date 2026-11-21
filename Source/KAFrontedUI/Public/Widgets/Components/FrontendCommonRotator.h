// RoadMap Komronbek Alimkulov - Allright 
//Parent - UCommonRotator

#pragma once

#include "CoreMinimal.h"
#include "CommonRotator.h"

#include "FrontendCommonRotator.generated.h"


UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class KAFRONTEDUI_API UFrontendCommonRotator : public UCommonRotator
{
	GENERATED_BODY()
	
//METHODS
public:
	void SetSelectedOptionByText(const FText& InTextOption);
};
