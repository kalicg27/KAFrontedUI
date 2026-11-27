// RoadMap Komronbek Alimkulov - Allright 


#include "FrontendSettings/KAFrontendLoadScreenSettings.h"
#include "Blueprint/UserWidget.h"

TSubclassOf<UUserWidget> UKAFrontendLoadScreenSettings::GetLoadingScreenWidgetClassChecked() const
{
    checkf(!SoftloadingScreenWidgetClass.IsNull(), TEXT("Forgot to assign a valid bluerpint widget bro"));
    TSubclassOf<UUserWidget> LoadedLoadingScreenWidget = SoftloadingScreenWidgetClass.LoadSynchronous();

    return LoadedLoadingScreenWidget;
}
