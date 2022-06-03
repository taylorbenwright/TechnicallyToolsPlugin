
#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"


class SDoubleScrollBox : public SCompoundWidget
{
public:
	
	SLATE_BEGIN_ARGS(SDoubleScrollBox)
	{}

	SLATE_ARGUMENT(TSharedPtr<SWidget>, Content)
	SLATE_ARGUMENT(EVisibility, ScrollbarVisibility)
	
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	TSharedRef<class SScrollBox> GetHorizontalScrollbox() const {return HorizontalScrollBox.ToSharedRef();}
	TSharedRef<class SScrollBox> GetVerticalScrollbox() const {return VerticalScrollBox.ToSharedRef();}

	void SetScrollBarVisibility(EVisibility InVisibility);

private:
	FReply OnBorderMouseDown(const FGeometry& Geometry, const FPointerEvent& PointerEvent);
	FReply OnBorderMouseMove(const FGeometry& Geometry, const FPointerEvent& PointerEvent);
	FReply OnBorderMouseUp(const FGeometry& Geometry, const FPointerEvent& PointerEvent);
	
	/* SWidget virtuals */
	virtual bool SupportsKeyboardFocus() const override { return true; }
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;

	
	TSharedPtr<class SScrollBox> VerticalScrollBox;
	TSharedPtr<class SScrollBar> VerticalScrollBar;
	
	TSharedPtr<class SScrollBox> HorizontalScrollBox;
	TSharedPtr<class SScrollBar> HorizontalScrollBar;

	bool RightMouseButtonDown = false;
};