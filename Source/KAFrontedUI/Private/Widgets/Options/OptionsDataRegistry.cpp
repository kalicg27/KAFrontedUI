// RoadMap Komronbek Alimkulov - Allright 


#include "Widgets/Options/OptionsDataRegistry.h"

#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"
#include "Widgets/Options/DataObjects/ListDataObject_String.h"
#include "Widgets/Options/OptionsDataInteractionHelper.h"
#include "FrontendSettings/FrontendGameUserSettings.h"
#include "FrontendFunctionLibrary.h"
#include "FrontendGameplayTags.h"
#include "Widgets/Options/DataObjects/ListDataObject_Scalar.h"

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
	VIdeoTabCollection->SetDataDisplayName(FText::FromString(TEXT("VIdeo")));
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
