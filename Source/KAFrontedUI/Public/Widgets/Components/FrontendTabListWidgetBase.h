// RoadMap Komronbek Alimkulov - Allright 
//Parent - UCommonTabListWidgetBase
#pragma once

#include "CoreMinimal.h"
#include "CommonTabListWidgetBase.h"

#include "FrontendTabListWidgetBase.generated.h"

//Forward Declarations
class UFrontendCommonButtonBase;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class KAFRONTEDUI_API UFrontendTabListWidgetBase : public UCommonTabListWidgetBase
{
	GENERATED_BODY()

//METHODS
//FrontendTabListWidgetBase
public:
	void RequestRegisterTab(const FName& InTabID, const FText& InTabDisplayName);

//UE
private:
	//From UWidget
#if WITH_EDITOR	
	virtual void ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const override;
#endif

//PROPERTIES
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Tab List Settings", meta = (AllowPrivateAccess = "true", ClampMin = "1", ClampMax = "10"))
	int32 DebugEditorPreviewTabCount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Tab List Settings", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UFrontendCommonButtonBase> TabButtonEntryWidgetClass;

};
