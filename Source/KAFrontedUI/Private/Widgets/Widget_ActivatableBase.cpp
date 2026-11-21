// RoadMap Komronbek Alimkulov - Allright 


#include "Widgets/Widget_ActivatableBase.h"

#include "Controllers/FrontedUIPlayerController.h"

// Widget_ActivatableBase
AFrontedUIPlayerController* UWidget_ActivatableBase::GetOwningFrontendUIPlayerController()
{
	if (!CachedOwningFrontendPC.IsValid())
	{
		CachedOwningFrontendPC = GetOwningPlayer<AFrontedUIPlayerController>();
	}
	return CachedOwningFrontendPC.IsValid()? CachedOwningFrontendPC.Get() : nullptr;
}
