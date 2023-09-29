// Copyright by Savvas JRD - LTD Cyprus


#include "Actor/RpgEffectActor.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/RpgAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
ARpgEffectActor::ARpgEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("OverlapSphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void ARpgEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	/* TODO: Change it to apply a GamePlayEffect, for now using const_Cast as a hack. Remove it After. */
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const URpgAttributeSet* RpgAttributeSet = Cast <URpgAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(URpgAttributeSet::StaticClass()));
		
		URpgAttributeSet* MutableRpgAttributeSet = const_cast<URpgAttributeSet*>(RpgAttributeSet);
		MutableRpgAttributeSet->SetHealth(RpgAttributeSet->GetHealth() + 50.f);

		Destroy();
	}
}

void ARpgEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

// Called when the game starts or when spawned
void ARpgEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ARpgEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ARpgEffectActor::EndOverlap);
}

// Called every frame
//void ARpgEffectActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

