// Copyright by Savvas JRD - LTD Cyprus


#include "UI/WidgetController/RpgWidgetController.h"

void URpgWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;

	PlayerState = WCParams.PlayerState;

	AbilitySystemComponent = WCParams.AbilitySystemComponent;

	AttributeSet = WCParams.AttributeSet;
}

void URpgWidgetController::BroadcastInitialValues()
{
	
}

void URpgWidgetController::BindCallbacksToDependencies()
{

}
