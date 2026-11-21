// RoadMap Komronbek Alimkulov - Allright 


#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"

void UListDataObject_Collection::AddChildListData(UListDataObject_Base* InChildListData)
{
    //notife the child list data to init itself
    InChildListData->InitDataObject();
    //set the child list data's paretn to this
    InChildListData->SetParentData(this);
    ChildListDataArray.Add(InChildListData);
}

TArray<UListDataObject_Base*> UListDataObject_Collection::GetAllChildListData() const
{
    return ChildListDataArray;
}

bool UListDataObject_Collection::HasAnyChildListData() const
{
    return !ChildListDataArray.IsEmpty();
}
