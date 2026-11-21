// RoadMap Komronbek Alimkulov - Allright 


#include "Controllers/FrontedUIPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"

//UE
void AFrontedUIPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(), FName("Default"), FoundCameras);

	//validation of Founded Cameras
	if (!FoundCameras.IsEmpty())
	{
		SetViewTarget(FoundCameras[0]);
	}

}
