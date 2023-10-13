// Copyright by Savvas JRD - LTD Cyprus


#include "RpgAssetManager.h"

#include "RpgGameplayTags.h"

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
}
