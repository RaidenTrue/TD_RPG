// Copyright by Savvas JRD - LTD Cyprus


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/RpgAttributeSet.h"
#include "RpgGameplayTags.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	/*Super::BindCallbacksToDependencies();*/

	
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	/*Super::BroadcastInitialValues();*/

	URpgAttributeSet* AS = CastChecked<URpgAttributeSet>(AttributeSet);

	check(AttributeInfo);

	FRpgAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FRpgGameplayTags::Get().Attributes_Primary_Strength);

	Info.AttributeValue = AS->GetStrength();

	AttributeInfoDelegate.Broadcast(Info);
}
