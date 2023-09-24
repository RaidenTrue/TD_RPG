// Copyright by Savvas JRD - LTD Cyprus


#include "Character/RpgBaseCharacter.h"

// Sets default values
ARpgBaseCharacter::ARpgBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARpgBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARpgBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARpgBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

