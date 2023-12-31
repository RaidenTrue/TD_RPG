// Copyright by Savvas JRD - LTD Cyprus


#include "AbilitySystem/Abilities/RpgProjectileSpell.h"

#include "RpgGameplayTags.h"
#include "AbilitySystemComponent.h"
#include "Actor/RpgProjectile.h"
#include "Interfaces/CombatInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
//#include "Kismet/KismetSystemLibrary.h"

void URpgProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	/*UKismetSystemLibrary::PrintString(this, FString("ActivateAbility (C++)"), true, true, FLinearColor::Green, 5.f);*/
}

void URpgProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();

	if (!bIsServer) { return; }

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), SocketTag);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();

	if (bOverridePitch)
	{
		Rotation.Pitch = PitchOverride;
	}

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());

	ARpgProjectile* Projectile = GetWorld()->SpawnActorDeferred<ARpgProjectile>(
		ProjectileClass, SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	/* TODO: Give the Projectile a GameplayEffectSpec for causing Damage. */

	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();

	TArray<TWeakObjectPtr<AActor>> Actors;
	Actors.Add(Projectile);

	FHitResult HitResult;
	HitResult.Location = ProjectileTargetLocation;

	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(Projectile);
	EffectContextHandle.AddActors(Actors);

	EffectContextHandle.AddHitResult(HitResult);

	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);

	const FRpgGameplayTags GameplayTags = FRpgGameplayTags::Get();

	for (auto& Pair : DamageTypes)
	{
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());

		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaledDamage);
	}

	/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("FireBolt Damage: %f"), ScaledDamage));*/

	Projectile->DamageEffectSpecHandle = SpecHandle;

	Projectile->FinishSpawning(SpawnTransform);

	/*ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());


	if (CombatInterface)
	{
		
	}*/
}
