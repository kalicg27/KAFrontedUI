// RoadMap Komronbek Alimkulov - Allright 
//Parent - UUserWidget
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Widget_OptionsDetailsView.generated.h"

//Forward Declarations
class UCommonTextBlock;
class UCommonLazyImage;
class UCommonRichTextBlock;
class UListDataObject_Base;


UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class KAFRONTEDUI_API UWidget_OptionsDetailsView : public UUserWidget
{
	GENERATED_BODY()

//METHODS
//Widget_OptionsDetailsView
public:
	void UpdateDetailsViewInfo(UListDataObject_Base* InDataObject, const FString& InEntryWidgetClassName = FString());
	void ClearDetailsViewInfo();

//UE
protected:
	//from UUserWidget
	virtual void NativeOnInitialized() override;

//BIND WIDGETS
private:
	//bound widgets
	UPROPERTY(meta = (BindWidget))
	UCommonTextBlock* CommonTextBlock_Title;

	UPROPERTY(meta = (BindWidget))
	UCommonLazyImage* CommonLazyImage_DescriptionImage;

	UPROPERTY(meta = (BindWidget))
	UCommonRichTextBlock* CommonRichText_Description;

	UPROPERTY(meta = (BindWidget))
	UCommonRichTextBlock* CommonRichText_DynamicDetails;

	UPROPERTY(meta = (BindWidget))
	UCommonRichTextBlock* CommonRichText_DisabledReason;

	
};
