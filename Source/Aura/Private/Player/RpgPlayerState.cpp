// Copyright by Savvas JRD - LTD Cyprus


#include "Player/RpgPlayerState.h"
#include "AbilitySystem/RpgAttributeSet.h"
#include "AbilitySystem/RpgAbilitySystemComponent.h"

ARpgPlayerState::ARpgPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<URpgAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<URpgAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* ARpgPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
