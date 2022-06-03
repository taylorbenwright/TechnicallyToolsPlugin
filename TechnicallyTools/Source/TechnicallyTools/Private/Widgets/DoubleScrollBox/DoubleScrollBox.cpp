
#include "Widgets/DoubleScrollBox/DoubleScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "Widgets/DoubleScrollBox/SDoubleScrollBox.h"

UDoubleScrollBox::UDoubleScrollBox()
	: DesiredVerticalScrollOffset(0)
	, DesiredHorizontalScrollOffset(0)
{
}

void UDoubleScrollBox::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	MyDoubleScrollBox->SetScrollBarVisibility(UWidget::ConvertSerializedVisibilityToRuntime(ScrollBarVisibility));
}

void UDoubleScrollBox::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyDoubleScrollBox.Reset();
}

UClass* UDoubleScrollBox::GetSlotClass() const
{
	return UScrollBoxSlot::StaticClass();
}

void UDoubleScrollBox::OnSlotAdded(UPanelSlot* inSlot)
{
	// Add the child to the live canvas if it already exists
	if ( MyDoubleScrollBox.IsValid() )
	{
		CastChecked<UScrollBoxSlot>(inSlot)->BuildSlot(MyDoubleScrollBox->GetHorizontalScrollbox());
	}
}

void UDoubleScrollBox::OnSlotRemoved(UPanelSlot* inSlot)
{
	// Remove the widget from the live slot if it exists.
	if ( MyDoubleScrollBox.IsValid() && inSlot->Content)
	{
		TSharedPtr<SWidget> Widget = inSlot->Content->GetCachedWidget();
		if ( Widget.IsValid() )
		{
			MyDoubleScrollBox->GetHorizontalScrollbox()->RemoveSlot(Widget.ToSharedRef());
		}
	}
}

TSharedRef<SWidget> UDoubleScrollBox::RebuildWidget()
{
	MyDoubleScrollBox = SNew(SDoubleScrollBox)
		.ScrollbarVisibility(EVisibility::Collapsed);

	for (UPanelSlot* PanelSlot : Slots)
	{
		if (UScrollBoxSlot* TypedSlot = Cast<UScrollBoxSlot>(PanelSlot))
		{
			TypedSlot->Parent = this;
			TypedSlot->BuildSlot(MyDoubleScrollBox->GetHorizontalScrollbox());
		}
	}
	
	return MyDoubleScrollBox.ToSharedRef();
}
