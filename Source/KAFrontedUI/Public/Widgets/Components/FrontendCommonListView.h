// RoadMap Komronbek Alimkulov - Allright 
//Parent - UCommonListView

#pragma once

#include "CoreMinimal.h"
#include "CommonListView.h"

#include "FrontendCommonListView.generated.h"

//Forward Declarations
class UDataAsset_DataListEntryMapping;

UCLASS()
class KAFRONTEDUI_API UFrontendCommonListView : public UCommonListView
{
	GENERATED_BODY()

//METHODS
//FrontendCommon - ListView
protected:
	// taking from UCommonlistView interface;
	virtual UUserWidget& OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) override;

	//From ListViewBase
	virtual bool OnIsSelectableOrNavigableInternal(UObject* FirstSelectedItem) override;
//UE
private:
	//From UWidget
#if WITH_EDITOR	
	virtual void ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const override;
#endif
	
//PROPERTIES
private:
	UPROPERTY(EditAnywhere, Category= "Frontend List View Settings")
	UDataAsset_DataListEntryMapping* DataListEntryMapping;

	
};
