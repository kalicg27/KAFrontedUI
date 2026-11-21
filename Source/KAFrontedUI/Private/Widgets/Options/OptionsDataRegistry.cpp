// RoadMap Komronbek Alimkulov - Allright 


#include "Widgets/Options/OptionsDataRegistry.h"

#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"
#include "Widgets/Options/DataObjects/ListDataObject_String.h"
#include "Widgets/Options/OptionsDataInteractionHelper.h"
#include "FrontendSettings/FrontendGameUserSettings.h"
#include "FrontendFunctionLibrary.h"
#include "FrontendGameplayTags.h"

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
		{
			UListDataObject_String* TestItem = NewObject<UListDataObject_String>();
			TestItem->SetDataID(FName("TestItem"));
			TestItem->SetDataDisplayName(FText::FromString(TEXT("Test Item Bro")));

			VolumeCategoryCollection->AddChildListData(TestItem);
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
