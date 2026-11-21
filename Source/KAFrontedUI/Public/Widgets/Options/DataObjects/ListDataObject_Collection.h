// RoadMap Komronbek Alimkulov - Allright 
//Parent - UListDataObject_Base

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/DataObjects/ListDataObject_Base.h"

#include "ListDataObject_Collection.generated.h"


UCLASS()
class KAFRONTEDUI_API UListDataObject_Collection : public UListDataObject_Base
{
	GENERATED_BODY()

//METHODS
//ListDataObject_Collection
public:
	void AddChildListData(UListDataObject_Base* InChildListData);

//UListDataObject_Base
public:
	virtual TArray<UListDataObject_Base*> GetAllChildListData() const;
	virtual bool HasAnyChildListData() const;

//PROPERTIES
private:
	UPROPERTY(Transient)
	TArray<UListDataObject_Base*> ChildListDataArray;

	
};
