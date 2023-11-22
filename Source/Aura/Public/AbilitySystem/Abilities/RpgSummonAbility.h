// Copyright by Savvas JRD - LTD Cyprus

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/RpgGameplayAbility.h"
#include "RpgSummonAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API URpgSummonAbility : public URpgGameplayAbility
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations();

	UFUNCTION(BlueprintPure, Category = Summoning)
	TSubclassOf<APawn> GetRandomMinionClass();

	UPROPERTY(EditAnywhere, Category = Summoning)
	int32 NumMinions = 5;

	UPROPERTY(EditDefaultsOnly, Category = Summoning)
	TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(EditDefaultsOnly, Category = Summoning)
	float MinSpawnDistance = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = Summoning)
	float MaxSpawnDistance = 250.f;

	UPROPERTY(EditDefaultsOnly, Category = Summoning)
	float SpawnSpread = 90.f;

};
