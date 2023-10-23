// Copyright by Savvas JRD - LTD Cyprus


#include "Actor/RpgProjectile.h"

// Sets default values
ARpgProjectile::ARpgProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARpgProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARpgProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

