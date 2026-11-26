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
	
//STRUCT
public:
	UFrontendGameUserSettings();

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

	//Audio Tab
	UFUNCTION()
	float GetOverallVolume() const { return OverallVolume; }

	UFUNCTION()
	void SetOverallVolume(float InVolume);

	UFUNCTION()
	float GetMusicVolume() const { return MusicVolume; }

	UFUNCTION()
	void SetMusicVolume(float InVolume);

	UFUNCTION()
	float GetSoundFXVolume() const { return SoundFXVolume; }

	UFUNCTION()
	void SetSoundFXVolume(float InVolume);

	UFUNCTION()
	bool GetAllowBackgroundAuido() const { return bAllowBackgroundAudio; }

	UFUNCTION()
	void SetAllowBackgroundAudio(bool bIsAllowed);

	UFUNCTION()
	bool GetUseHDRAudioMode() const { return bShouldUseHDRAudioMode; }

	UFUNCTION()
	void SetUseHDRAudioMode(bool bIsAllowed);

	//display category settings
	UFUNCTION()
	float GetCurrentDisplayGamma() const;

	UFUNCTION()
	void SetCurrentDisplayGamma(float InNewGamma);

//PROPERTIES
private:
	//Gameplay tab
	UPROPERTY(Config)
	FString CurrentGameDifficulty;

	UPROPERTY(Config)
	FString CurrentTestMode;

	//Audio Tab
	UPROPERTY(Config)
	float OverallVolume;

	UPROPERTY(Config)
	float MusicVolume;

	UPROPERTY(Config)
	float SoundFXVolume;
	
	UPROPERTY(Config)
	bool bAllowBackgroundAudio;

	UPROPERTY(Config)
	bool bShouldUseHDRAudioMode;
};
