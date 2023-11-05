// Copyright by Savvas JRD - LTD Cyprus


#include "Actor/RpgProjectile.h"
#include "Aura/Aura.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"


ARpgProjectile::ARpgProjectile()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");	
	SetRootComponent(Sphere);

	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);

	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = 550.f;

	ProjectileMovement->ProjectileGravityScale = 0.f;
}


void ARpgProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeSpan);

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ARpgProjectile::OnSphereOverlap);

	TrailLoopSoundComponent = UGameplayStatics::SpawnSoundAttached(TrailLoopSound, GetRootComponent());
	
}

void ARpgProjectile::Destroyed()
{
	if (!bHit && !HasAuthority())
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());

		if (TrailLoopSoundComponent) TrailLoopSoundComponent->Stop();
	}

	Super::Destroyed();
}

void ARpgProjectile::OnSphereOverlap(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (DamageEffectSpecHandle.Data.IsValid() && DamageEffectSpecHandle.Data.Get()->GetContext().GetEffectCauser() == OtherActor) { return; }

	if (!bHit)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
	}

	if (TrailLoopSoundComponent) TrailLoopSoundComponent->Stop();

	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}

		Destroy();
	}
	else
	{
		bHit = true;
	}
}


//void ARpgProjectile::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

