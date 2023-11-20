// Copyright by Savvas JRD - LTD Cyprus

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/RpgDamageGameplayAbility.h"
#include "RpgProjectileSpell.generated.h"

class ARpgProjectile;
class UGameplayEffect;

struct FGameplayTag;

/**
 * 
 */
UCLASS()
class AURA_API URpgProjectileSpell : public URpgDamageGameplayAbility
{
	GENERATED_BODY()

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category = Projectile)
	void SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ARpgProjectile> ProjectileClass;
	
};
