// Copyright by Savvas JRD - LTD Cyprus


#include "Character/RpgCharacter.h"
#include "Camera/CameraComponent.h"

#include "Player/RpgPlayerState.h"
#include "Player/RpgPlayerController.h"

#include "AbilitySystem/RpgAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "UI/HUD/RpgHUD.h"

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

int32 ARpgCharacter::GetPlayerLevel()
{
	const ARpgPlayerState* RpgPlayerState = GetPlayerState<ARpgPlayerState>();

	check(RpgPlayerState);

	return RpgPlayerState->GetPlayerLevel();
}

void ARpgCharacter::InitAbilityActorInfo()
{
	ARpgPlayerState* RpgPlayerState = GetPlayerState<ARpgPlayerState>();

	/* Assert for Valid RpgPlayerState. */
	check(RpgPlayerState);

	RpgPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(RpgPlayerState, this);

	Cast<URpgAbilitySystemComponent>(RpgPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();

	AbilitySystemComponent = RpgPlayerState->GetAbilitySystemComponent();
	AttributeSet = RpgPlayerState->GetAttributeSet();

	if (ARpgPlayerController* RpgPlayerController = Cast<ARpgPlayerController>(GetController()))
	{
		if (ARpgHUD* RpgHUD = Cast<ARpgHUD>(RpgPlayerController->GetHUD()))
		{
			RpgHUD->InitOverlay(RpgPlayerController, RpgPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	InitializeDefaultAttributes();
}
