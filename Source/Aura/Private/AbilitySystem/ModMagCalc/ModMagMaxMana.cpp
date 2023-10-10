// Copyright by Savvas JRD - LTD Cyprus


#include "AbilitySystem/ModMagCalc/ModMagMaxMana.h"

#include "AbilitySystem/RpgAttributeSet.h"
#include "Interfaces/CombatInterface.h"

UModMagMaxMana::UModMagMaxMana()
{
	IntelligenceDef.AttributeToCapture = URpgAttributeSet::GetIntelligenceAttribute();

	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	IntelligenceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UModMagMaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	/* Gather TAgs from Source & Target. */

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;

	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Intelligence = 0.f;

	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluationParameters, Intelligence);

	Intelligence = FMath::Max<float>(Intelligence, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());

	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 50.f + 2.f * Intelligence + 10.f * PlayerLevel;
}
