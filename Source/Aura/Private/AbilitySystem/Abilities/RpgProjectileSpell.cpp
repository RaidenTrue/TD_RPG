// Copyright by Savvas JRD - LTD Cyprus


#include "AbilitySystem/Abilities/RpgProjectileSpell.h"

#include "Actor/RpgProjectile.h"
#include "Interfaces/CombatInterface.h"
//#include "Kismet/KismetSystemLibrary.h"

void URpgProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	/*UKismetSystemLibrary::PrintString(this, FString("ActivateAbility (C++)"), true, true, FLinearColor::Green, 5.f);*/
}

void URpgProjectileSpell::SpawnProjectile()
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();

	if (!bIsServer) { return; }

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());

	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);

		/* TODO: Set the Projectile Rotation. */

		ARpgProjectile* Projectile = GetWorld()->SpawnActorDeferred<ARpgProjectile>(
			ProjectileClass, SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		/* TODO: Give the Projectile a GameplayEffectSpec for causing Damage. */

		Projectile->FinishSpawning(SpawnTransform);
	}
}
