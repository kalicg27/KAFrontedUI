// RoadMap Komronbek Alimkulov - Allright 


#include "FrontendSettings/FrontendGameUserSettings.h"

UFrontendGameUserSettings* UFrontendGameUserSettings::Get()
{
	if (GEngine)
	{
		return CastChecked< UFrontendGameUserSettings>(GEngine->GetGameUserSettings());
	}

	return nullptr;
}
