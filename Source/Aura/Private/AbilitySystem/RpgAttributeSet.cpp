// Copyright by Savvas JRD - LTD Cyprus


#include "AbilitySystem/RpgAttributeSet.h"
#include "Net/UnrealNetwork.h"

URpgAttributeSet::URpgAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);

	InitMana(100.f);
	InitMaxMana(100.f);
}

void URpgAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(URpgAttributeSet, Health, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(URpgAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(URpgAttributeSet, Mana, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(URpgAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void URpgAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URpgAttributeSet, Health, OldHealth);
}

void URpgAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URpgAttributeSet, MaxHealth, OldMaxHealth);
}

void URpgAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URpgAttributeSet, Mana, OldMana);
}

void URpgAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URpgAttributeSet, MaxMana, OldMaxMana);
}
