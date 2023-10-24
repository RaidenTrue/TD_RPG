// Copyright by Savvas JRD - LTD Cyprus


#include "RpgAssetManager.h"

#include "RpgGameplayTags.h"
#include "AbilitySystemGlobals.h"

URpgAssetManager& URpgAssetManager::Get()
{
	check(GEngine);

	URpgAssetManager* RpgAssetManager = Cast<URpgAssetManager>(GEngine->AssetManager);

	return *RpgAssetManager;
}

void URpgAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FRpgGameplayTags::InitializeNativeGameplayTags();

	/* Required in order to use TargetData! */
	UAbilitySystemGlobals::Get().InitGlobalData();
}
