// Copyright by Savvas JRD - LTD Cyprus

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * RpgGameplayTags
 * 
 * This is a Singleton, containing Native GameplayTags.
 */

struct FRpgGameplayTags
{

public:

	static const FRpgGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeGameplayTags();

	/* Primary Attributes. */

	FGameplayTag Attributes_Primary_Strength;

	FGameplayTag Attributes_Primary_Intelligence;

	FGameplayTag Attributes_Primary_Resilience;

	FGameplayTag Attributes_Primary_Vigor;

	/* Secondary Attributes. */

	FGameplayTag Attributes_Secondary_Armor;

	FGameplayTag Attributes_Secondary_ArmorPenetration;

	FGameplayTag Attributes_Secondary_BlockChance;

	FGameplayTag Attributes_Secondary_CriticalHitChance;

	FGameplayTag Attributes_Secondary_CriticalHitDamage;

	FGameplayTag Attributes_Secondary_CriticalHitResistance;

	FGameplayTag Attributes_Secondary_HealthRegeneration;

	FGameplayTag Attributes_Secondary_ManaRegeneration;

	FGameplayTag Attributes_Secondary_MaxHealth;

	FGameplayTag Attributes_Secondary_MaxMana;

	/* Resistance Gameplay Tags. */

	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Lightning;
	FGameplayTag Attributes_Resistance_Arcane;

	FGameplayTag Attributes_Resistance_Physical;

	/* Input Gameplay Tags. */

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;

	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;

	FGameplayTag InputTag_4;

	/* General Attributes. */

	FGameplayTag Damage;

	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Arcane;

	FGameplayTag Damage_Physical;

	FGameplayTag Abilities_Attack;

	/* Combat Sockets. */

	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_RightHand;
	FGameplayTag CombatSocket_LeftHand;
	FGameplayTag CombatSocket_Tail;

	FGameplayTag Montage_Attack_01;
	FGameplayTag Montage_Attack_02;
	FGameplayTag Montage_Attack_03;
	FGameplayTag Montage_Attack_04;

	/* End Combat Sockets. */

	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;

	TArray<FGameplayTag> DamageTypes;

	FGameplayTag Effects_HitReact;

private:

	static FRpgGameplayTags GameplayTags;

};
