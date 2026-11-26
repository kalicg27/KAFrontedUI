// RoadMap Komronbek Alimkulov - Allright 


#include "Widgets/Options/OptionsDataRegistry.h"

#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"
#include "Widgets/Options/DataObjects/ListDataObject_String.h"
#include "Widgets/Options/OptionsDataInteractionHelper.h"
#include "FrontendSettings/FrontendGameUserSettings.h"
#include "FrontendFunctionLibrary.h"
#include "FrontendGameplayTags.h"
#include "Widgets/Options/DataObjects/ListDataObject_Scalar.h"
#include "Widgets/Options/DataObjects/ListDataObject_StringResolution.h"

//MACROS
#define MAKE_OPTIONS_DATA_CONTROL(SetterOrGetterFuncName) \
	MakeShared<FOptionsDataInteractionHelper>(GET_FUNCTION_NAME_STRING_CHECKED(UFrontendGameUserSettings, SetterOrGetterFuncName))

//OptionsDataRegistry
void UOptionsDataRegistry::InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer)
{
	InitGameplayCollectionTab();
	InitAudioCollectionTab();
	InitVideoCollectionTab();
	InitControlCollectionTab();
	InitCheatsCollectionTab();
}

TArray<UListDataObject_Base*> UOptionsDataRegistry::GetListSourceItemsBySelectedTabID(const FName& InSelectedTabID) const
{
	UListDataObject_Collection* const* FoundTabCollectionPtr = RegisteredOptionsTabCollections.FindByPredicate(
		[InSelectedTabID](UListDataObject_Collection* AvailableTabCollection)->bool
		{
			return AvailableTabCollection->GetDataID() == InSelectedTabID; 
		}
	);
	checkf(FoundTabCollectionPtr, TEXT("NO Valid tab dounf under the ID %s"), *InSelectedTabID.ToString()); 

	UListDataObject_Collection* FoundTabCollection = *FoundTabCollectionPtr;
	//return FoundTabCollection->GetAllChildListData();
	TArray< UListDataObject_Base*> AllChildListItems;
	for (UListDataObject_Base* ChildListData : FoundTabCollection->GetAllChildListData())
	{
		if (!ChildListData)
		{
			continue;
		}
		AllChildListItems.Add(ChildListData);
		if (ChildListData->HasAnyChildListData())
		{
			FindChildListDataRecursively(ChildListData, AllChildListItems);
		}
	}
	return AllChildListItems;
}

void UOptionsDataRegistry::FindChildListDataRecursively(UListDataObject_Base* InParentData, TArray<UListDataObject_Base*>& OutFoundChildListData) const
{
	if (!InParentData || !InParentData->HasAnyChildListData())
	{
		return;
	}
	for (UListDataObject_Base* SubChildListData : InParentData->GetAllChildListData())
	{
		if (!SubChildListData)
		{
			continue;
		}
		OutFoundChildListData.Add(SubChildListData);
		if (SubChildListData->HasAnyChildListData())
		{
			FindChildListDataRecursively(SubChildListData, OutFoundChildListData);
		}
	}
	
}

//Initialize Collection tabs
void UOptionsDataRegistry::InitGameplayCollectionTab()
{
	UListDataObject_Collection* GameplayTabCollection = NewObject<UListDataObject_Collection>();
	GameplayTabCollection->SetDataID(FName("GameplayTabCollection"));
	GameplayTabCollection->SetDataDisplayName(FText::FromString(TEXT("Gameplay")));

	//this is the full code for contrustor data interactor helper, hard coded baby
	//TSharedPtr< FOptionsDataInteractionHelper> ConstructedHelper= MakeShared<FOptionsDataInteractionHelper>(GET_FUNCTION_NAME_STRING_CHECKED(UFrontendGameUserSettings, GetCurrentGameDifficulty));
	
	//game deficulty
	{
		UListDataObject_String* GameDifficulty = NewObject<UListDataObject_String>();
		GameDifficulty->SetDataID(FName("Game Difficulty"));
		GameDifficulty->SetDataDisplayName(FText::FromString(TEXT("Diffuculty")));

		GameDifficulty->SetDescrtiptionRichText(FText::FromString(TEXT("Adjust game diffucly if it is hard or easy for you, boy!\
			\n\n<Bold>Easy-Peasy:</> Only for focusing on the story it self and experience.\
			Provides the most relaxing time you ever had in this game bro\
			\n\n<Bold>Normal:</> It is just normal bro\
			\n\n<Bold>Hard:</> For focusing diffuctl stuff\
			\n\n<Bold>Very hard:</> Only for focusing on the story it self and experience.")));

		GameDifficulty->AddDynamicOption(TEXT("Easy-Peasy"), FText::FromString(TEXT("Easy-Peasy")));
		GameDifficulty->AddDynamicOption(TEXT("Normal"), FText::FromString(TEXT("Normal")));
		GameDifficulty->AddDynamicOption(TEXT("Hard"), FText::FromString(TEXT("Hard")));
		GameDifficulty->AddDynamicOption(TEXT("Very Hard"), FText::FromString(TEXT("Very Hard")));

		GameDifficulty->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetCurrentGameDifficulty));
		GameDifficulty->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetCurrentGameDifficulty));
		//GameDifficulty->SetSoftDecriptionImage(UFrontendFunctionLibrary::GetOptionsSoftImageByTag(FrontendGameplayTags::Frontend_Image_Test2Image));
		GameDifficulty->SetDefaultValueFromString(TEXT("Normal"));

		GameDifficulty->SetShouldApplySettingsImmediately(true);

		GameplayTabCollection->AddChildListData(GameDifficulty);
	}
	
	//test item
	{
		UListDataObject_String* TestItem = NewObject<UListDataObject_String>();
		TestItem->SetDataID(FName("Test Baby"));
		TestItem->SetDataDisplayName(FText::FromString(TEXT("This is Test one")));

		TestItem->SetDescrtiptionRichText(FText::FromString(TEXT("Adjust game diffucly if it is hard or easy for you, boy!\
			\n\n<Bold>Test1:</> Only for focusing on the story it self and experience.\
			Provides the most relaxing time you ever had in this game bro\
			\n\n<Bold>Test2:</> It is just normal bro\
			\n\n<Bold>Terst3:</> For focusing diffuctl stuff\
			\n\n<Bold>TE3t4:</> Only fthis is a test ence.")));

		TestItem->AddDynamicOption(TEXT("TestOne"), FText::FromString(TEXT("TestOne")));
		TestItem->AddDynamicOption(TEXT("TestTwo"), FText::FromString(TEXT("TestTwo")));
		TestItem->AddDynamicOption(TEXT("TestThree"), FText::FromString(TEXT("Test Three")));
		TestItem->AddDynamicOption(TEXT("TestFour"), FText::FromString(TEXT("Test Four")));
		TestItem->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetCurrentTestMode));
		TestItem->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetCurrentTestMode));
		TestItem->SetSoftDecriptionImage(UFrontendFunctionLibrary::GetOptionsSoftImageByTag(FrontendGameplayTags::Frontend_Image_TestImage));

		TestItem->SetDefaultValueFromString(TEXT("TestOne"));

		TestItem->SetShouldApplySettingsImmediately(true);

		GameplayTabCollection->AddChildListData(TestItem);
	}

	RegisteredOptionsTabCollections.Add(GameplayTabCollection);
}

void UOptionsDataRegistry::InitAudioCollectionTab()
{
	UListDataObject_Collection* AudioTabCollection = NewObject<UListDataObject_Collection>();
	AudioTabCollection->SetDataID(FName("AudioTabCollection"));
	AudioTabCollection->SetDataDisplayName(FText::FromString(TEXT("Audio")));

	
	//Volume Category 
	{
		UListDataObject_Collection* VolumeCategoryCollection= NewObject<UListDataObject_Collection>();
		VolumeCategoryCollection->SetDataID(FName("VolumeCategoryCollection"));
		VolumeCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Volume")));
		AudioTabCollection->AddChildListData(VolumeCategoryCollection);
		//test item
		//{
		//	UListDataObject_String* TestItem = NewObject<UListDataObject_String>();
		//	TestItem->SetDataID(FName("TestItem"));
		//	TestItem->SetDataDisplayName(FText::FromString(TEXT("Test Item Bro")));

		//	VolumeCategoryCollection->AddChildListData(TestItem);
		//}

		//Global Volume
		{
			UListDataObject_Scalar* OverallVolume = NewObject < UListDataObject_Scalar > ();
			OverallVolume->SetDataID(FName("OverallVolume"));
			OverallVolume->SetDataDisplayName(FText::FromString(TEXT("Global Volume")));
			OverallVolume->SetDescrtiptionRichText(FText::FromString(TEXT("Please configure Global volume")));
			OverallVolume->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			OverallVolume->SetOutputValueRange(TRange<float>(0.f, 1.f));
			OverallVolume->SetSliderStepSize(0.01f);
			OverallVolume->SetDefaultValueFromString(LexToString(0.5f));
			OverallVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
			OverallVolume->SetNumberFormattingOptions(UListDataObject_Scalar::NoDecimal());

			OverallVolume->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetOverallVolume));
			OverallVolume->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetOverallVolume));

			OverallVolume->SetShouldApplySettingsImmediately(true);

			VolumeCategoryCollection->AddChildListData(OverallVolume);
		}

		//Music Volume:
		{
			UListDataObject_Scalar* MusicVolume = NewObject < UListDataObject_Scalar >();
			MusicVolume->SetDataID(FName("MusicVolume"));
			MusicVolume->SetDataDisplayName(FText::FromString(TEXT("Music Volume")));
			MusicVolume->SetDescrtiptionRichText(FText::FromString(TEXT("Please configure Music volume")));
			MusicVolume->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			MusicVolume->SetOutputValueRange(TRange<float>(0.f, 1.f));
			MusicVolume->SetSliderStepSize(0.01f);
			MusicVolume->SetDefaultValueFromString(LexToString(0.5f));
			MusicVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
			MusicVolume->SetNumberFormattingOptions(UListDataObject_Scalar::NoDecimal());

			MusicVolume->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetMusicVolume));
			MusicVolume->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetMusicVolume));

			MusicVolume->SetShouldApplySettingsImmediately(true);

			VolumeCategoryCollection->AddChildListData(MusicVolume);
		}

		//Sounds fx
		{
			UListDataObject_Scalar* SoundFXVolume = NewObject < UListDataObject_Scalar >();
			SoundFXVolume->SetDataID(FName("SoundFXVolume"));
			SoundFXVolume->SetDataDisplayName(FText::FromString(TEXT("SoundFX Volume")));
			SoundFXVolume->SetDescrtiptionRichText(FText::FromString(TEXT("Please configure SoundFX volume")));
			SoundFXVolume->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			SoundFXVolume->SetOutputValueRange(TRange<float>(0.f, 1.f));
			SoundFXVolume->SetSliderStepSize(0.01f);
			SoundFXVolume->SetDefaultValueFromString(LexToString(0.5f));
			SoundFXVolume->SetDisplayNumericType(ECommonNumericType::Percentage);
			SoundFXVolume->SetNumberFormattingOptions(UListDataObject_Scalar::NoDecimal());

			SoundFXVolume->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetSoundFXVolume));
			SoundFXVolume->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetSoundFXVolume));

			SoundFXVolume->SetShouldApplySettingsImmediately(true);

			VolumeCategoryCollection->AddChildListData(SoundFXVolume);
		}

		
		
	}

	//Sound Category
	{
		UListDataObject_Collection* SoundCategoryCollection = NewObject<UListDataObject_Collection>();
		SoundCategoryCollection->SetDataID(FName("SoundCategoryCollection"));
		SoundCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Sound")));

		AudioTabCollection->AddChildListData(SoundCategoryCollection);

		//Allow Background Audio
		{
			UListDataObject_StringBool* AllowBackgroundAudio= NewObject<UListDataObject_StringBool>();
			AllowBackgroundAudio->SetDataID(FName("AllowBackgroundAudio"));
			AllowBackgroundAudio->SetDataDisplayName(FText::FromString(TEXT("Allow Background Audio")));
			AllowBackgroundAudio->OverrideTrueDisplayText(FText::FromString(TEXT("Enabled")));
			AllowBackgroundAudio->OverrideFalseDisplayText(FText::FromString(TEXT("Disabled")));
			AllowBackgroundAudio->SetFalseAsDefaultValue();
			AllowBackgroundAudio->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetAllowBackgroundAuido));
			AllowBackgroundAudio->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetAllowBackgroundAudio));
			AllowBackgroundAudio->SetShouldApplySettingsImmediately(true);

			SoundCategoryCollection->AddChildListData(AllowBackgroundAudio);
		}
		
		//HDr Audio:
		{
			UListDataObject_StringBool* UseHDRAudioMode = NewObject<UListDataObject_StringBool>();
			UseHDRAudioMode->SetDataID(FName("UseHDRAudioMode"));
			UseHDRAudioMode->SetDataDisplayName(FText::FromString(TEXT("Use HDR Audio Mode")));
			UseHDRAudioMode->OverrideTrueDisplayText(FText::FromString(TEXT("Enabled")));
			UseHDRAudioMode->OverrideFalseDisplayText(FText::FromString(TEXT("Disabled")));
			UseHDRAudioMode->SetFalseAsDefaultValue();
			UseHDRAudioMode->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetUseHDRAudioMode));
			UseHDRAudioMode->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetUseHDRAudioMode));
			UseHDRAudioMode->SetShouldApplySettingsImmediately(true);

			SoundCategoryCollection->AddChildListData(UseHDRAudioMode);
		}
	}

	RegisteredOptionsTabCollections.Add(AudioTabCollection);
}

void UOptionsDataRegistry::InitVideoCollectionTab()
{
	UListDataObject_Collection* VIdeoTabCollection = NewObject<UListDataObject_Collection>();
	VIdeoTabCollection->SetDataID(FName("VIdeoTabCollection"));
	VIdeoTabCollection->SetDataDisplayName(FText::FromString(TEXT("Video")));

	UListDataObject_StringEnum* CreatedWindowMode = nullptr;
	//category display
	{
		UListDataObject_Collection* DisplayCategoryCollection = NewObject<UListDataObject_Collection>();
		DisplayCategoryCollection->SetDataID(FName("DispayCategoryCollection"));
		DisplayCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Display")));

		VIdeoTabCollection->AddChildListData(DisplayCategoryCollection);

		FOptionsDataEditConditionDescriptor PackegedBuildOnlyContion;
		PackegedBuildOnlyContion.SetEditConfitionFunc(
			[]()->bool
			{
				const bool bIsInEditor = GIsEditor || GIsPlayInEditorWorld;
				return !bIsInEditor;
			}
		);

		PackegedBuildOnlyContion.SetDisabledRichReason(TEXT("\n\n<Dissabled>This settings can be adjusted only in package settings bro.</>"));

		//window mode part
		{
			UListDataObject_StringEnum* WindowModeS = NewObject<UListDataObject_StringEnum>();
			WindowModeS->SetDataID(FName("WindowMode"));
			WindowModeS->SetDataDisplayName(FText::FromString(TEXT("Window Mode Bro")));
			WindowModeS->SetDisabledRichText(FText::FromString(TEXT("Here goes my dicription for WIndow mode, change your resolution and glasses bro")));
			WindowModeS->AddEnumOptions(EWindowMode::Fullscreen, FText::FromString(TEXT("FullScreen Mode")));
			WindowModeS->AddEnumOptions(EWindowMode::WindowedFullscreen, FText::FromString(TEXT("No Borders Window Bro")));
			WindowModeS->AddEnumOptions(EWindowMode::Windowed, FText::FromString(TEXT("Windowed Bro")));
			WindowModeS->SetDefaultValueFromEnumOption(EWindowMode::WindowedFullscreen);
			WindowModeS->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetFullscreenMode));
			WindowModeS->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetFullscreenMode));
			WindowModeS->SetShouldApplySettingsImmediately(true);
			WindowModeS->AddEditCondition(PackegedBuildOnlyContion);
			CreatedWindowMode = WindowModeS;
			DisplayCategoryCollection->AddChildListData(WindowModeS);
		}

		//resolutin settings
		{
			UListDataObject_StringResolution* ScreenResolution = NewObject<UListDataObject_StringResolution>();
			ScreenResolution->SetDataID(FName("ScreenResolution"));
			ScreenResolution->SetDataDisplayName(FText::FromString(TEXT("Screen Resolution")));
			ScreenResolution->SetDisabledRichText(FText::FromString(TEXT("Here goes my dicription for Screen Resolution, change your resolution and glasses bro")));
			ScreenResolution->InitResolutionValues();
			ScreenResolution->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetScreenResolution));
			ScreenResolution->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetScreenResolution));
			ScreenResolution->SetShouldApplySettingsImmediately(true);

			ScreenResolution->AddEditCondition(PackegedBuildOnlyContion);

			FOptionsDataEditConditionDescriptor WindowModeEditonCondition;
			WindowModeEditonCondition.SetEditConfitionFunc(
				[CreatedWindowMode]()->bool
				{
					const bool bIsBorderlessWindow = CreatedWindowMode->GetCurrentValueAsEnum<EWindowMode::Type>() == EWindowMode::WindowedFullscreen;
					return !bIsBorderlessWindow;
				}
			);
			WindowModeEditonCondition.SetDisabledRichReason(TEXT("\n\n<Dissabled>Screen resolution can be changed while the window mode is set to 'BOrderles window'</>"));
			WindowModeEditonCondition.SetDisabledForcedStringValue(ScreenResolution->GetMaximumAllowedResolution());
			ScreenResolution->AddEditCondition(WindowModeEditonCondition);

			ScreenResolution->AddEditDependecyData(CreatedWindowMode);

			DisplayCategoryCollection->AddChildListData(ScreenResolution);

		}
	}

	//Graphics Category
	{
		UListDataObject_Collection* GraphicsCategoryCollection = NewObject<UListDataObject_Collection>();
		GraphicsCategoryCollection->SetDataID(FName("GraphicsCategoryCollection"));
		GraphicsCategoryCollection->SetDataDisplayName(FText::FromString(TEXT("Graphics")));

		VIdeoTabCollection->AddChildListData(GraphicsCategoryCollection);

		//Display gamma
		{
			UListDataObject_Scalar* DisplayGamma= NewObject<UListDataObject_Scalar>();
			DisplayGamma->SetDataID(FName("DisplayGamma"));
			DisplayGamma->SetDataDisplayName(FText::FromString(TEXT("Brightness")));
			DisplayGamma->SetDescrtiptionRichText(FText::FromString(TEXT("This is soem text for you bro, adjust the brightness bro")));
			DisplayGamma->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			DisplayGamma->SetOutputValueRange(TRange<float>(1.7f, 2.7f));
			DisplayGamma->SetDisplayNumericType(ECommonNumericType::Percentage);
			DisplayGamma->SetNumberFormattingOptions(UListDataObject_Scalar::NoDecimal());
			DisplayGamma->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetCurrentDisplayGamma));
			DisplayGamma->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetCurrentDisplayGamma));
			DisplayGamma->SetDefaultValueFromString(LexToString(2.2f));

			GraphicsCategoryCollection->AddChildListData(DisplayGamma);
		}

		UListDataObject_StringInteger* CreatedOverallQuality = nullptr;
		//overall quality
		{
			UListDataObject_StringInteger* OverallQuality = NewObject< UListDataObject_StringInteger>();
			OverallQuality->SetDataID(FName("OverallQuality"));
			OverallQuality->SetDataDisplayName(FText::FromString(TEXT("Overall Quality")));
			OverallQuality->SetDescrtiptionRichText(FText::FromString(TEXT("This is soem text for you bro, adjust the overall quality bro")));
			OverallQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			OverallQuality->AddIntegerOption(1, FText::FromString(TEXT("Normal")));
			OverallQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			OverallQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			OverallQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			OverallQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetOverallScalabilityLevel));
			OverallQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetOverallScalabilityLevel));
			OverallQuality->SetShouldApplySettingsImmediately(true);

			GraphicsCategoryCollection->AddChildListData(OverallQuality);

			CreatedOverallQuality = OverallQuality;
		}

		//resolution scale
		{
			UListDataObject_Scalar* ResolutionScale = NewObject<UListDataObject_Scalar>();
			ResolutionScale->SetDataID(FName("ResolutionScale"));
			ResolutionScale->SetDataDisplayName(FText::FromString(TEXT("3D Resolution BRO")));
			ResolutionScale->SetDescrtiptionRichText(FText::FromString(TEXT("This is soem text for you bro, adjust the Resolution Scale bro")));
			ResolutionScale->SetDisplayValueRange(TRange<float>(0.f, 1.f));
			ResolutionScale->SetOutputValueRange(TRange<float>(0.f, 1.f));
			ResolutionScale->SetDisplayNumericType(ECommonNumericType::Percentage);
			ResolutionScale->SetNumberFormattingOptions(UListDataObject_Scalar::NoDecimal());
			ResolutionScale->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetResolutionScaleNormalized));
			ResolutionScale->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetResolutionScaleNormalized));
			ResolutionScale->SetShouldApplySettingsImmediately(true);

			ResolutionScale->AddEditDependecyData(CreatedOverallQuality);

			GraphicsCategoryCollection->AddChildListData(ResolutionScale);
		}
		//global illuminutation 
		{
			UListDataObject_StringInteger* GlobalIlluminationQuality = NewObject< UListDataObject_StringInteger>();
			GlobalIlluminationQuality->SetDataID(FName("GlobalIlluminationQuality"));
			GlobalIlluminationQuality->SetDataDisplayName(FText::FromString(TEXT("Global Illumination")));
			GlobalIlluminationQuality->SetDescrtiptionRichText(FText::FromString(TEXT("This is soem text for you bro, adjust the Global Illumination Quality bro")));
			GlobalIlluminationQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			GlobalIlluminationQuality->AddIntegerOption(1, FText::FromString(TEXT("Normal")));
			GlobalIlluminationQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			GlobalIlluminationQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			GlobalIlluminationQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			GlobalIlluminationQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetGlobalIlluminationQuality));
			GlobalIlluminationQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetGlobalIlluminationQuality));
			GlobalIlluminationQuality->SetShouldApplySettingsImmediately(true);

			GlobalIlluminationQuality->AddEditDependecyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependecyData(GlobalIlluminationQuality);
			GraphicsCategoryCollection->AddChildListData(GlobalIlluminationQuality);

		}
		//shadow quality
		{
			UListDataObject_StringInteger* ShadowQuality = NewObject< UListDataObject_StringInteger>();
			ShadowQuality->SetDataID(FName("ShadowQuality"));
			ShadowQuality->SetDataDisplayName(FText::FromString(TEXT("Shadow Quality")));
			ShadowQuality->SetDescrtiptionRichText(FText::FromString(TEXT("This is soem text for you bro, adjust the Shadow Quality bro")));
			ShadowQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			ShadowQuality->AddIntegerOption(1, FText::FromString(TEXT("Normal")));
			ShadowQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			ShadowQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			ShadowQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			ShadowQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetShadowQuality));
			ShadowQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetShadowQuality));
			ShadowQuality->SetShouldApplySettingsImmediately(true);

			ShadowQuality->AddEditDependecyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependecyData(ShadowQuality);
			GraphicsCategoryCollection->AddChildListData(ShadowQuality);

		}
		//antiAliasing Quality
		{
			UListDataObject_StringInteger* AntiAliasingQuality = NewObject< UListDataObject_StringInteger>();
			AntiAliasingQuality->SetDataID(FName("AntiAliasingQuality"));
			AntiAliasingQuality->SetDataDisplayName(FText::FromString(TEXT("AntiAliasing Quality")));
			AntiAliasingQuality->SetDescrtiptionRichText(FText::FromString(TEXT("This is soem text for you bro, adjust the AntiAliasing Quality bro")));
			AntiAliasingQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			AntiAliasingQuality->AddIntegerOption(1, FText::FromString(TEXT("Normal")));
			AntiAliasingQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			AntiAliasingQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			AntiAliasingQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			AntiAliasingQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetAntiAliasingQuality));
			AntiAliasingQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetAntiAliasingQuality));
			AntiAliasingQuality->SetShouldApplySettingsImmediately(true);

			AntiAliasingQuality->AddEditDependecyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependecyData(AntiAliasingQuality);
			GraphicsCategoryCollection->AddChildListData(AntiAliasingQuality);

		}
		//VewDistance Quality
		{
			UListDataObject_StringInteger* ViewDistanceQuality = NewObject< UListDataObject_StringInteger>();
			ViewDistanceQuality->SetDataID(FName("ViewDistanceQuality"));
			ViewDistanceQuality->SetDataDisplayName(FText::FromString(TEXT("View Distance Quality")));
			ViewDistanceQuality->SetDescrtiptionRichText(FText::FromString(TEXT("This is some text for you bro, adjust the View Distance Quality bro")));
			ViewDistanceQuality->AddIntegerOption(0, FText::FromString(TEXT("Near")));
			ViewDistanceQuality->AddIntegerOption(1, FText::FromString(TEXT("Medium")));
			ViewDistanceQuality->AddIntegerOption(2, FText::FromString(TEXT("Far")));
			ViewDistanceQuality->AddIntegerOption(3, FText::FromString(TEXT("Very far")));
			ViewDistanceQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			ViewDistanceQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetViewDistanceQuality));
			ViewDistanceQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetViewDistanceQuality));
			ViewDistanceQuality->SetShouldApplySettingsImmediately(true);

			ViewDistanceQuality->AddEditDependecyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependecyData(ViewDistanceQuality);
			GraphicsCategoryCollection->AddChildListData(ViewDistanceQuality);

		}

		//Texture Quality
		{
			UListDataObject_StringInteger* TextureQuality = NewObject< UListDataObject_StringInteger>();
			TextureQuality->SetDataID(FName("TextureQuality"));
			TextureQuality->SetDataDisplayName(FText::FromString(TEXT("Texture Quality")));
			TextureQuality->SetDescrtiptionRichText(FText::FromString(TEXT("This is soem text for you bro, adjust the Texture Quality bro")));
			TextureQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			TextureQuality->AddIntegerOption(1, FText::FromString(TEXT("Normal")));
			TextureQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			TextureQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			TextureQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			TextureQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetTextureQuality));
			TextureQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetTextureQuality));
			TextureQuality->SetShouldApplySettingsImmediately(true);

			TextureQuality->AddEditDependecyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependecyData(TextureQuality);
			GraphicsCategoryCollection->AddChildListData(TextureQuality);

		}
		//Visual Effects Quality
		{
			UListDataObject_StringInteger* VisualEffectQuality = NewObject< UListDataObject_StringInteger>();
			VisualEffectQuality->SetDataID(FName("VisualEffectQuality"));
			VisualEffectQuality->SetDataDisplayName(FText::FromString(TEXT("Visual Effect Quality")));
			VisualEffectQuality->SetDescrtiptionRichText(FText::FromString(TEXT("This is soem text for you bro, adjust the VisualEffect Quality bro")));
			VisualEffectQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			VisualEffectQuality->AddIntegerOption(1, FText::FromString(TEXT("Normal")));
			VisualEffectQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			VisualEffectQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			VisualEffectQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			VisualEffectQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetVisualEffectQuality));
			VisualEffectQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetVisualEffectQuality));
			VisualEffectQuality->SetShouldApplySettingsImmediately(true);

			VisualEffectQuality->AddEditDependecyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependecyData(VisualEffectQuality);
			GraphicsCategoryCollection->AddChildListData(VisualEffectQuality);
		}
		//Reflection Quality
		{
			UListDataObject_StringInteger* ReflectionQuality = NewObject< UListDataObject_StringInteger>();
			ReflectionQuality->SetDataID(FName("ReflectionQuality"));
			ReflectionQuality->SetDataDisplayName(FText::FromString(TEXT("Reflectiont Quality")));
			ReflectionQuality->SetDescrtiptionRichText(FText::FromString(TEXT("This is soem text for you bro, adjust the Reflectiont Quality bro")));
			ReflectionQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			ReflectionQuality->AddIntegerOption(1, FText::FromString(TEXT("Normal")));
			ReflectionQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			ReflectionQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			ReflectionQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			ReflectionQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetReflectionQuality));
			ReflectionQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetReflectionQuality));
			ReflectionQuality->SetShouldApplySettingsImmediately(true);

			ReflectionQuality->AddEditDependecyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependecyData(ReflectionQuality);
			GraphicsCategoryCollection->AddChildListData(ReflectionQuality);

		}
		//post Processing Quality
		{
			UListDataObject_StringInteger* PostProcessingQuality = NewObject< UListDataObject_StringInteger>();
			PostProcessingQuality->SetDataID(FName("PostProcessingQuality"));
			PostProcessingQuality->SetDataDisplayName(FText::FromString(TEXT("Post Processing Quality")));
			PostProcessingQuality->SetDescrtiptionRichText(FText::FromString(TEXT("This is soem text for you bro, adjust the Post Processing Quality bro")));
			PostProcessingQuality->AddIntegerOption(0, FText::FromString(TEXT("Low")));
			PostProcessingQuality->AddIntegerOption(1, FText::FromString(TEXT("Normal")));
			PostProcessingQuality->AddIntegerOption(2, FText::FromString(TEXT("High")));
			PostProcessingQuality->AddIntegerOption(3, FText::FromString(TEXT("Epic")));
			PostProcessingQuality->AddIntegerOption(4, FText::FromString(TEXT("Cinematic")));
			PostProcessingQuality->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetPostProcessingQuality));
			PostProcessingQuality->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetPostProcessingQuality));
			PostProcessingQuality->SetShouldApplySettingsImmediately(true);

			PostProcessingQuality->AddEditDependecyData(CreatedOverallQuality);
			CreatedOverallQuality->AddEditDependecyData(PostProcessingQuality);
			GraphicsCategoryCollection->AddChildListData(PostProcessingQuality);
		}
	}

	RegisteredOptionsTabCollections.Add(VIdeoTabCollection);
}

void UOptionsDataRegistry::InitControlCollectionTab()
{
	UListDataObject_Collection* ControlTabCollection = NewObject<UListDataObject_Collection>();
	ControlTabCollection->SetDataID(FName("ControlTabCollection"));
	ControlTabCollection->SetDataDisplayName(FText::FromString(TEXT("Control")));
	RegisteredOptionsTabCollections.Add(ControlTabCollection);
}

void UOptionsDataRegistry::InitCheatsCollectionTab()
{
	UListDataObject_Collection* CheatsTabCollection = NewObject<UListDataObject_Collection>();
	CheatsTabCollection->SetDataID(FName("CheatsTabCollection"));
	CheatsTabCollection->SetDataDisplayName(FText::FromString(TEXT("Cheats")));
	RegisteredOptionsTabCollections.Add(CheatsTabCollection);
}
