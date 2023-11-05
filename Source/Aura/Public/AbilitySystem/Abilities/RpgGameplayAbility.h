// Copyright by Savvas JRD - LTD Cyprus

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RpgGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API URpgGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = Input)
	FGameplayTag StartupInputTag;
	
};
