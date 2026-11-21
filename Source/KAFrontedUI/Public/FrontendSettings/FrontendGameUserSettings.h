// RoadMap Komronbek Alimkulov - Allright 
//Parent - UGameUserSettings
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"

#include "FrontendGameUserSettings.generated.h"

UCLASS()
class KAFRONTEDUI_API UFrontendGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
	
//METHODS
//FrontendGameUsetSettings
public:
	static UFrontendGameUserSettings* Get();

	//gameplay collection tab
	UFUNCTION()
	FString GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }

	UFUNCTION()
	void SetCurrentGameDifficulty(const FString& InNewDifficulty) { CurrentGameDifficulty = InNewDifficulty; }

	UFUNCTION()
	FString GetCurrentTestMode() const { return CurrentTestMode; }

	UFUNCTION()
	void SetCurrentTestMode(const FString& InNewMode) { CurrentTestMode = InNewMode; }
	//gameplay collection tab

	

//PROPERTIES
private:
	UPROPERTY(Config)
	FString CurrentGameDifficulty;

	UPROPERTY(Config)
	FString CurrentTestMode;

	
};
