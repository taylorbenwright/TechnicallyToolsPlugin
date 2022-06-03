
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Styling/SlateTypes.h"
#include "Widgets/SWidget.h"
#include "Components/PanelWidget.h"
#include "DoubleScrollBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserScrolledEvent, float, CurrentOffset);

/**
 * A scrollable area that can go both left/right, and up/down. Doesn't support virtualization.
 */
UCLASS()
class TECHNICALLYTOOLS_API UDoubleScrollBox : public UPanelWidget
{
	GENERATED_BODY()
public:

	UDoubleScrollBox();

	/** Visibility */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Double Scroll Box")
	ESlateVisibility ScrollBarVisibility;

	//~ Begin UWidget Interface
	virtual void SynchronizeProperties() override;
	//~ End UWidget Interface

	//~ Begin UVisual Interface
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	//~ End UVisual Interface

	protected:
	// UPanelWidget
	virtual UClass* GetSlotClass() const override;
	virtual void OnSlotAdded(UPanelSlot* inSlot) override;
	virtual void OnSlotRemoved(UPanelSlot* inSlot) override;
	// End UPanelWidget
	
	float DesiredVerticalScrollOffset;
	float DesiredHorizontalScrollOffset;

	TSharedPtr<class SDoubleScrollBox> MyDoubleScrollBox;
	
	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	//~ End UWidget Interface
};