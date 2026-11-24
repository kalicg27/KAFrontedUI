// RoadMap Komronbek Alimkulov - Allright 


#include "Controllers/FrontedUIPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "FrontendSettings/FrontendGameUserSettings.h"

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

	UFrontendGameUserSettings* GameUserSettings= UFrontendGameUserSettings::Get();

	if (GameUserSettings->GetLastCPUBenchmarkResult() == -1.f || GameUserSettings->GetLastGPUBenchmarkResult())
	{
		GameUserSettings->RunHardwareBenchmark();
		GameUserSettings->ApplyHardwareBenchmarkResults();
	}

}
