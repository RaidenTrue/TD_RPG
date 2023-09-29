// Copyright by Savvas JRD - LTD Cyprus


#include "UI/Widget/RpgUserWidget.h"

void URpgUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;

	WidgetControllerSet();
}

