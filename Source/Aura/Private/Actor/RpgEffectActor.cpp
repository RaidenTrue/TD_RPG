// Copyright by Savvas JRD - LTD Cyprus


#include "Actor/RpgEffectActor.h"

// Sets default values
ARpgEffectActor::ARpgEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARpgEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARpgEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

