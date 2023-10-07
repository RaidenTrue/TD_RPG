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
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const URpgAttributeSet* RpgAttributeSet = CastChecked<URpgAttributeSet>(AttributeSet);

	/* Refactored Implementation with Lambdas - No FunctionCallback. */

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RpgAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RpgAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RpgAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RpgAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);

	Cast<URpgAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda([this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				/* For example: Tag = Mesasge.HealthPotion */
				/* "Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False. */
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));

				if (Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);

					MessageWidgetRowDelegate.Broadcast(*Row);
				}

				/*const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());

				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, Msg);*/
			}
		}
	);
}
