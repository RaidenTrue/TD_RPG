// Copyright by Savvas JRD - LTD Cyprus


#include "RpgGameplayTags.h"

#include "GameplayTagsManager.h"

FRpgGameplayTags FRpgGameplayTags::GameplayTags;

void FRpgGameplayTags::InitializeNativeGameplayTags()
{
	/* Primary Attributes Initialization. */

	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"), FString("Increases Damage"));

	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"), FString("Increases Spell Damage."));

	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Resilience"), FString("Increases Armor & Armor Penetration."));

	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"), FString("Increases Health"));

	/* Secondary Attributes Initialization. */

	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"), FString("Decreases taken Damage, increases Block Chance."));

	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"), FString("Penetrates Armor Blocking capabilities."));

	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"), FString("Increases Chance to Block an Attack."));

	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance"), FString("Increases Chance for causing a Critical Hit."));

	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitDamage"), FString("Increases Critical Hit Damage."));

	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitResistance"), FString("Increases Resistance of a Critical Hit."));

	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"), FString("Increases the Amount of Health Regenerated Over Time."));

	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"), FString("Increases the Amount of Mana Regenerated Over Time."));

	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"), FString("Increases the Total Amount of Health points."));

	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"), FString("Increases the Total Amount of Mana points"));

	/* Input GameplayTags. */

	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"), FString("Input Tag for the Left Mouse Button."));

	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"), FString("Input Tag for the Right Mouse Button."));

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"), FString("Input Tag for the Numeric Key 1."));

	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"), FString("Input Tag for the Numeric Key 2."));

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"), FString("Input Tag for the Numeric Key 3."));

	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"), FString("Input Tag for the Numeric Key 4."));

	/* General Attributes. */

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage"), FString("Damage Tag."));

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.HitReact"), FString("Tag granted when Hit Reacting."));
}
