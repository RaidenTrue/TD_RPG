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

	FGameplayTag Attributes_Secondary_Armor;

protected:

private:

	static FRpgGameplayTags GameplayTags;

};
