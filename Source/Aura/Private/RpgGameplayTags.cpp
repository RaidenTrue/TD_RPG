// Copyright by Savvas JRD - LTD Cyprus


#include "RpgGameplayTags.h"

#include "GameplayTagsManager.h"

FRpgGameplayTags FRpgGameplayTags::GameplayTags;

void FRpgGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Decreases taken Damage, increases Block Chance."));
}
