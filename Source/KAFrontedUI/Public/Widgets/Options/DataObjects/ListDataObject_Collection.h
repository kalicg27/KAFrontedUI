// RoadMap Komronbek Alimkulov - Allright 

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/DataObjects/ListDataObject_Base.h"
#include "ListDataObject_Collection.generated.h"

/**
 * 
 */
UCLASS()
class KAFRONTEDUI_API UListDataObject_Collection : public UListDataObject_Base
{
	GENERATED_BODY()


public:
	void AddChildListData(UListDataObject_Base* InChildListData);

	//begin ULIstDataOBject 
	virtual TArray<UListDataObject_Base*> GetAllChildListData() const;
	virtual bool HasAnyChildListData() const;
private:
	UPROPERTY(Transient)
	TArray<UListDataObject_Base*> ChildListDataArray;

	
};
