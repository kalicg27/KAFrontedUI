// RoadMap Komronbek Alimkulov - Allright 


#include "AsyncActions/AsyncAction_PushSoftWidget.h"

#include "Subsystem/FrontendUISybsystem.h"
#include "Widgets/Widget_ActivatableBase.h"

//AsyncAction_PushSoftWidget
UAsyncAction_PushSoftWidget* UAsyncAction_PushSoftWidget::PushSoftWidget(const UObject* WorldContextObject, APlayerController* OwningPlayerController, TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass, UPARAM(meta = (Categories = "Frontend.WidgetStack")) FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget)
{
	checkf(!InSoftWidgetClass.IsNull(), TEXT("PushSoftWidgetToStack was passed a null soft widget class"))

	if (GEngine)
	{	
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			UAsyncAction_PushSoftWidget* Node = NewObject<UAsyncAction_PushSoftWidget>();
			Node->CashedOwningWorld = World;
			Node->CashedOwningPC = OwningPlayerController;
			Node->CashedSoftWidgetClass = InSoftWidgetClass;
			Node->CashedWidgetStackTag = InWidgetStackTag;
			Node->bCashedbFocusOnNewlyPushedWidget = bFocusOnNewlyPushedWidget;
			
			Node->RegisterWithGameInstance(World);
			return Node;
			
		}

	}

	return nullptr;
}

//from UBlueprintAsyncActionBase
void UAsyncAction_PushSoftWidget::Activate()
{
	UFrontendUISybsystem* FrontendUISybsystem = UFrontendUISybsystem::Get(CashedOwningWorld.Get());
	FrontendUISybsystem->PushSoftWidgetToStackAnynsc(CashedWidgetStackTag, CashedSoftWidgetClass,
		[this](EAsyncPushWidgetSlate InPushState, UWidget_ActivatableBase* PushedWidget)
		{
			switch (InPushState)
			{
			case EAsyncPushWidgetSlate::OnCreatedBeforePush:
				PushedWidget->SetOwningPlayer(CashedOwningPC.Get());
				OnWidgetCreatedBeforePush.Broadcast(PushedWidget);
				break;
			case EAsyncPushWidgetSlate::AfterPush:
				AfterPush.Broadcast(PushedWidget);
				if (bCashedbFocusOnNewlyPushedWidget)
				{
					if (UWidget* WidgetToFocus = PushedWidget->GetDesiredFocusTarget())
					{
						WidgetToFocus->SetFocus();
					}
				}
				
				SetReadyToDestroy();
				break;
			default:
				break;
			}
		}
	);
}
