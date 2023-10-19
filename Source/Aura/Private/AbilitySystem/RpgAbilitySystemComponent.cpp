// Copyright by Savvas JRD - LTD Cyprus


#include "AbilitySystem/RpgAbilitySystemComponent.h"

#include "RpgGameplayTags.h"

void URpgAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &URpgAbilitySystemComponent::EffectApplied);

	/*FRpgGameplayTags::Get().Attributes_Primary_Intelligence;

	const FRpgGameplayTags& GameplayTags = FRpgGameplayTags::Get();*/

	//GameplayTags.Attributes_Secondary_Armor.ToString()

	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Secondary_Armor.ToString()));
}

void URpgAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		
		/*GiveAbility(AbilitySpec);*/

		GiveAbilityAndActivateOnce(AbilitySpec);
	}
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
