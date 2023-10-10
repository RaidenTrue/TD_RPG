// Copyright by Savvas JRD - LTD Cyprus

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "ModMagMaxHealth.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UModMagMaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:

	UModMagMaxHealth();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:


	FGameplayEffectAttributeCaptureDefinition VigorDef;
	
};
