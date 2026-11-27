// RoadMap Komronbek Alimkulov - Allright 


#include "Subsystem/KAFrontendLoadingScreenSubsystem.h"
#include "FrontendDebugHelper.h"

bool UKAFrontendLoadingScreenSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> FoundClasses;
		GetDerivedClasses(GetClass(), FoundClasses);
		return FoundClasses.IsEmpty();
	}

	return false;
}

void UKAFrontendLoadingScreenSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	FCoreUObjectDelegates::PreLoadMapWithContext.AddUObject(this, &ThisClass::OnMapPreLoaded);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ThisClass::OnMapPostLoaded);

}

void UKAFrontendLoadingScreenSubsystem::Deinitialize()
{
	FCoreUObjectDelegates::PreLoadMapWithContext.RemoveAll(this);
	FCoreUObjectDelegates::PostLoadMapWithWorld.RemoveAll(this);
}

UWorld* UKAFrontendLoadingScreenSubsystem::GetTickableGameObjectWorld() const
{
	if (UGameInstance* OwningGameInstance = GetGameInstance())
	{
		return OwningGameInstance->GetWorld();
	}
	return nullptr;
}

void UKAFrontendLoadingScreenSubsystem::Tick(float DeltaTime)
{
	Debug::Print(TEXT("bro is ticking"));
}

ETickableTickType UKAFrontendLoadingScreenSubsystem::GetTickableTickType() const
{
	if (IsTemplate())
	{
		return  ETickableTickType::Never;
	}
	return ETickableTickType::Conditional;
}

bool UKAFrontendLoadingScreenSubsystem::IsTickable() const
{

	return GetGameInstance() && GetGameInstance()->GetGameViewportClient();
}

TStatId UKAFrontendLoadingScreenSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UKAFrontendLoadingScreenSubsystem, STATGROUP_Tickables);
}

void UKAFrontendLoadingScreenSubsystem::OnMapPreLoaded(const FWorldContext& WorldContext, const FString& MapName)
{
	//Debug::Print(TEXT("On map pre loaded"));
}

void UKAFrontendLoadingScreenSubsystem::OnMapPostLoaded(UWorld* LoadedWorld)
{
	//Debug::Print(TEXT("On map post loaded")); //

}
