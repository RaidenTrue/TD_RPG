// Copyright by Savvas JRD - LTD Cyprus

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "RpgAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API URpgAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
