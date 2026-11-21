// RoadMap Komronbek Alimkulov - Allright 
//Parent - UObject

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OptionsDataRegistry.generated.h"

//Forward Declarations
class UListDataObject_Base;
class UListDataObject_Collection;

UCLASS()
class KAFRONTEDUI_API UOptionsDataRegistry : public UObject
{
	GENERATED_BODY()

//METHODS
//OptionsDataRegistry
public:
	//gets called by option screenr ight after the UOptionsDataRegistry is created;
	void InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer);

	const TArray<UListDataObject_Collection*>& GetRegisteredOptionsTabCollections() const { return RegisteredOptionsTabCollections; }

	TArray<UListDataObject_Base*> GetListSourceItemsBySelectedTabID(const FName& InSelectedTabID) const;

private:
	void FindChildListDataRecursively(UListDataObject_Base* InParentData, TArray<UListDataObject_Base*>& OutFoundChildListData) const;

	void InitGameplayCollectionTab();
	void InitAudioCollectionTab();
	void InitVideoCollectionTab();
	void InitControlCollectionTab();
	void InitCheatsCollectionTab();

//UE 

//PROPERTIES
private:
	UPROPERTY(Transient)
	TArray<UListDataObject_Collection*>RegisteredOptionsTabCollections;
};
