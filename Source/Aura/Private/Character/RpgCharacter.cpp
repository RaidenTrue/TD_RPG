// Copyright by Savvas JRD - LTD Cyprus


#include "Character/RpgCharacter.h"
#include "Camera/CameraComponent.h"
#include "Player/RpgPlayerState.h"
#include "AbilitySystem/RpgAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ARpgCharacter::ARpgCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	PlayerCamera->SetupAttachment(CameraBoom);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;

	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void ARpgCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	/* Init Ability Actor Info for the Server. */
	InitAbilityActorInfo();
}

void ARpgCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	/* InitAbilityActorInfo for the Client. */
	InitAbilityActorInfo();
}

void ARpgCharacter::InitAbilityActorInfo()
{
	ARpgPlayerState* RpgPlayerState = GetPlayerState<ARpgPlayerState>();

	/* Assert for Valid RpgPlayerState. */
	check(RpgPlayerState);

	RpgPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(RpgPlayerState, this);

	AbilitySystemComponent = RpgPlayerState->GetAbilitySystemComponent();
	AttributeSet = RpgPlayerState->GetAttributeSet();
}
