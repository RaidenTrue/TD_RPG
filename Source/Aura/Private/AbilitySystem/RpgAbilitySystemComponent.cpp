// Copyright by Savvas JRD - LTD Cyprus


#include "AbilitySystem/RpgAbilitySystemComponent.h"

void URpgAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &URpgAbilitySystemComponent::EffectApplied);
}

void URpgAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	/*GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::Green, FString("Effect is Applied."));*/

	FGameplayTagContainer TagContainer;

	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);

	//for (const FGameplayTag& Tag : TagContainer)
	//{
	//	/* TODO: Broadcast the Tag to the WidgetController. */

	//	const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());

	//	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, Msg);
	//}
}
