// RoadMap Komronbek Alimkulov - Allright 


#include "Widgets/Widget_PrimaryLayout.h"
#include "FrontendDebugHelper.h"

UCommonActivatableWidgetContainerBase* UWidget_PrimaryLayout::FindWidgetStackByTag(const FGameplayTag& InTag) const
{
	checkf(RegisteredWidgetStackMap.Contains(InTag), TEXT("Can not find any tags here by the tag %s"), *InTag.ToString());
	return RegisteredWidgetStackMap.FindRef(InTag);
}

void UWidget_PrimaryLayout::RegisterWidgetStack(UPARAM(meta = (Categories = "Frontend.WidgetStack")) FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InStack)
{
	if (!IsDesignTime())
	{
		if (!RegisteredWidgetStackMap.Contains(InStackTag))
		{
			//UE_LOG(LogTemp, Warning, TEXT("HELLOOO HERE is working ")); //that was just to check whether it works
			RegisteredWidgetStackMap.Add(InStackTag, InStack);
			//Debug::Print(TEXT("WIdget stack registered under the tag ") + InStackTag.ToString()); //removed becouse we stored in subsytem
		}
	}
}
 