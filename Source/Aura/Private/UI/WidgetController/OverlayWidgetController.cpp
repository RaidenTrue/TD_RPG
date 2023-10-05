// Copyright by Savvas JRD - LTD Cyprus


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/RpgAbilitySystemComponent.h"
#include "AbilitySystem/RpgAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const URpgAttributeSet* RpgAttributeSet = CastChecked<URpgAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(RpgAttributeSet->GetHealth());

	OnMaxHealthChanged.Broadcast(RpgAttributeSet->GetMaxHealth());

	OnManaChanged.Broadcast(RpgAttributeSet->GetMana());

	OnMaxManaChanged.Broadcast(RpgAttributeSet->GetMaxMana());

	/*AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RpgAttributeSet->GetHealthAttribute()).AddUObject(this, &)*/
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const URpgAttributeSet* RpgAttributeSet = CastChecked<URpgAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RpgAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RpgAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RpgAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RpgAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);

	Cast<URpgAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda([](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());

				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, Msg);
			}
		}
	);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
