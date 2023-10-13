// Copyright by Savvas JRD - LTD Cyprus

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "RpgAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API URpgAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	static URpgAssetManager& Get();

protected:

	virtual void StartInitialLoading();
	
};
