// RoadMap Komronbek Alimkulov - Allright 
//Parent - UCommonButtonBase
#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"

#include "FrontendCommonButtonBase.generated.h"

//Forward Declarations
class UCommonTextBlock;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class KAFRONTEDUI_API UFrontendCommonButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

//METHODS
//Frontend CommonButton_Base
public:
	UFUNCTION(BlueprintCallable)
	void SetButtonText(FText InText);

	UFUNCTION(BlueprintCallable)
	FText GetButtonDisplayText() const;

//UE
private:
	//from UUserWidget
	virtual void NativePreConstruct() override;

	//from UCommonButtonBase
	virtual void NativeOnCurrentTextStyleChanged() override;
	virtual void NativeOnHovered() override;
	virtual void NativeOnUnhovered() override;

//BIND WIDGETS
private:
	UPROPERTY(meta = (BindWidgetOptional))
	UCommonTextBlock* CommonTextBlock_ButtonText;

//PROPERTIES
//Frontend CommonButton_Base
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta = (AllowPrivateAccess = "true"))
	FText ButtonDisplayText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta = (AllowPrivateAccess = "true"))
	bool bUserUpperCaseForButtonText = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta = (AllowPrivateAccess = "true"))
	FText ButtonDescriptionText;

	
};
