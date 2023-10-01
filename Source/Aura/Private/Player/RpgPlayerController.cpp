// Copyright by Savvas JRD - LTD Cyprus


#include "Player/RpgPlayerController.h"
#include "Interfaces/EnemyInterface.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ARpgPlayerController::ARpgPlayerController()
{
	bReplicates = true;

}

void ARpgPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void ARpgPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(RpgContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(RpgContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;

	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);

	SetInputMode(InputModeData);
}

void ARpgPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARpgPlayerController::Move);
}

void ARpgPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ARpgPlayerController::CursorTrace()
{
	FHitResult CursorHit;

	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit);

	if (!CursorHit.bBlockingHit) { return; }

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/* Linetrace from Cursor. There are several Scenarios.
		A. LastActor is null & ThisActor is also null - Do Nothing.
		B. LastActor is null but ThisActor is Valid - Call Highlight ThisActor.
		C. LastActor is Valid & ThisActor is null - Call UnHighlight LastActor.
		D. LastActor is Valid & ThisActor is Valid, but LastActor != to ThisActor - UnHighlight LastActor & Highlight ThisActor.
		E. LastActor is Valid & ThisActor is Valid & both are the same Actor - Do Nothing.
	*/

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			/* Scenario B. */
			ThisActor->HighlightActor();
		}
		else
		{
			/* Both are null, Do Nothing - Case A. */
		}
	}

	else /* LastActor is Valid. */
	{
		if (ThisActor == nullptr)
		{
			/* Scenario C. */
			LastActor->UnHighlightActor();
		}
		else /* Both Actors are Valid. */
		{
			if (LastActor != ThisActor)
			{
				/* Scenario D. */
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				/* Scenario E. */
			}
		}
	}
}
