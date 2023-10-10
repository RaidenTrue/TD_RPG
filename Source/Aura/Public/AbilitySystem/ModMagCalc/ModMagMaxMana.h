// Copyright by Savvas JRD - LTD Cyprus

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "ModMagMaxMana.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UModMagMaxMana : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:

	UModMagMaxMana();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:

	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;
	
};
