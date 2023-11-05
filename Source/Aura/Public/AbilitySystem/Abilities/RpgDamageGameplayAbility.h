// Copyright by Savvas JRD - LTD Cyprus

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/RpgGameplayAbility.h"
#include "RpgDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API URpgDamageGameplayAbility : public URpgGameplayAbility
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	/* Removed due to Mapping out Damage in DamageTypes. */
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Damage)
	//FScalableFloat Damage;

	UPROPERTY(EditDefaultsOnly, Category = Damage)
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
	
};
