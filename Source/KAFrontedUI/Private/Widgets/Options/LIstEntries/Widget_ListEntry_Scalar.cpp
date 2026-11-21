// RoadMap Komronbek Alimkulov - Allright 


#include "Widgets/Options/LIstEntries/Widget_ListEntry_Scalar.h"
//From UUserWidget
void UWidget_ListEntry_Scalar::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}


//UListDataObject_Base
void UWidget_ListEntry_Scalar::OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);
}

void UWidget_ListEntry_Scalar::OnOwningListDataObjectModified(UListDataObject_Base* OwningModifiedData, EOptionslistDataModifyReason ModifyReason)
{
}

