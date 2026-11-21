// RoadMap Komronbek Alimkulov - Allright 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "FrontedUIPlayerController.generated.h"

UCLASS()
class KAFRONTEDUI_API AFrontedUIPlayerController : public APlayerController
{
	GENERATED_BODY()

//METHODS
//UE 
protected:
	//~ From APlayerController interface
	virtual void OnPossess(APawn* aPawn) override;
	
};
