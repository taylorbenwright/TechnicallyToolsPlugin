
#include "Widgets/DoubleScrollBox/SDoubleScrollBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Components/PanelWidget.h"


void SDoubleScrollBox::Construct(const FArguments& InArgs)
{

	HorizontalScrollBar = SNew(SScrollBar)
		.Orientation(Orient_Horizontal)
		.Visibility(InArgs._ScrollbarVisibility);
	
	VerticalScrollBar = SNew(SScrollBar)
		.Orientation(Orient_Vertical)
		.Visibility(InArgs._ScrollbarVisibility);
	
	ChildSlot
	[
		SNew(SBorder)
		.OnMouseButtonDown(FPointerEventHandler::CreateSP(this, &SDoubleScrollBox::OnBorderMouseDown))
		.OnMouseMove(FPointerEventHandler::CreateSP(this, &SDoubleScrollBox::OnBorderMouseMove))
		.OnMouseButtonUp(FPointerEventHandler::CreateSP(this, &SDoubleScrollBox::OnBorderMouseUp))
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.FillHeight(1.f)
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				[
					SAssignNew(VerticalScrollBox, SScrollBox)
					.Orientation(Orient_Vertical)
					.ExternalScrollbar(VerticalScrollBar)
					.ConsumeMouseWheel(EConsumeMouseWheel::Always)
					.AllowOverscroll(EAllowOverscroll::No)
					+SScrollBox::Slot()
					[
						SAssignNew(HorizontalScrollBox, SScrollBox)
						.Orientation(Orient_Horizontal)
						.ExternalScrollbar(HorizontalScrollBar)
						.ConsumeMouseWheel(EConsumeMouseWheel::Never)
						.AllowOverscroll(EAllowOverscroll::No)
						+SScrollBox::Slot()
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Top)
						[
							InArgs._Content.IsValid() ? InArgs._Content.ToSharedRef() : SNullWidget::NullWidget
						]
					]
				]
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					VerticalScrollBar.ToSharedRef()
				]
			]
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				HorizontalScrollBar.ToSharedRef()
			]
		]
	];
}

void SDoubleScrollBox::SetScrollBarVisibility(EVisibility InVisibility)
{
	HorizontalScrollBar->SetUserVisibility(InVisibility);
	VerticalScrollBar->SetUserVisibility(InVisibility);
}

FReply SDoubleScrollBox::OnBorderMouseDown(const FGeometry& Geometry, const FPointerEvent& PointerEvent)
{
	if (PointerEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		RightMouseButtonDown = true;
		SetCursor(EMouseCursor::GrabHand);
	}
	else
	{
		RightMouseButtonDown = false;
		SetCursor(EMouseCursor::Default);
	}
	return FReply::Handled();
}

FReply SDoubleScrollBox::OnBorderMouseMove(const FGeometry& Geometry, const FPointerEvent& PointerEvent)
{
	if (RightMouseButtonDown)
	{
		const FVector2D& cursorDelta = PointerEvent.GetCursorDelta();
		HorizontalScrollBox->SetScrollOffset(FMath::Clamp(HorizontalScrollBox->GetScrollOffset() + -cursorDelta.X, 0.f, HorizontalScrollBox->GetScrollOffsetOfEnd()));
		VerticalScrollBox->SetScrollOffset(FMath::Clamp(VerticalScrollBox->GetScrollOffset() + -cursorDelta.Y, 0.f, VerticalScrollBox->GetScrollOffsetOfEnd()));

		return FReply::Handled();
	}
	return FReply::Unhandled();
}

FReply SDoubleScrollBox::OnBorderMouseUp(const FGeometry& Geometry, const FPointerEvent& PointerEvent)
{
	if (PointerEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		RightMouseButtonDown = false;
		SetCursor(EMouseCursor::Default);
	}
	return FReply::Handled();
}

void SDoubleScrollBox::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	RightMouseButtonDown = false;
	SCompoundWidget::OnMouseLeave(MouseEvent);
}
