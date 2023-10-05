// Copyright by Savvas JRD - LTD Cyprus

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "RpgAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&  /*AssetTags*/);

/**
 * 
 */
UCLASS()
class AURA_API URpgAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	void AbilityActorInfoSet();

	FEffectAssetTags EffectAssetTags;

protected:

	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
	
};
