// Copyright by Savvas JRD - LTD Cyprus


#include "Player/RpgPlayerController.h"
#include "Interfaces/EnemyInterface.h"
#include "EnhancedInputSubsystems.h"
#include "Input/RpgInputComponent.h"
#include "Components/SplineComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "RpgGameplayTags.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "UI/Widget/DamageTextComponent.h"
#include "AbilitySystem/RpgAbilitySystemComponent.h"

ARpgPlayerController::ARpgPlayerController()
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void ARpgPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();

	AutoRun();
}

void ARpgPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter, bool bBlockedHit, bool bCriticalHit)
{
	if (IsValid(TargetCharacter) && DamageTextComponentClass && IsLocalController())
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);

		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

		DamageText->SetDamageText(DamageAmount, bBlockedHit, bCriticalHit);
	}
}

void ARpgPlayerController::AutoRun()
{
	if (!bAutoRunning) { return; }

	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);

		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();

		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
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

	/*UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);*/

	URpgInputComponent* RpgInputComponent = CastChecked<URpgInputComponent>(InputComponent);

	RpgInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARpgPlayerController::Move);
	RpgInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &ARpgPlayerController::ShiftPressed);
	RpgInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &ARpgPlayerController::ShiftReleased);

	RpgInputComponent->BindAdilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);

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
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit);

	if (!CursorHit.bBlockingHit) { return; }

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	if (LastActor != ThisActor)
	{
		if (LastActor) LastActor->UnHighlightActor();

		if (ThisActor) ThisActor->HighlightActor();
	}

	/* Linetrace from Cursor. There are several Scenarios.
		A. LastActor is null & ThisActor is also null - Do Nothing.
		B. LastActor is null but ThisActor is Valid - Call Highlight ThisActor.
		C. LastActor is Valid & ThisActor is null - Call UnHighlight LastActor.
		D. LastActor is Valid & ThisActor is Valid, but LastActor != to ThisActor - UnHighlight LastActor & Highlight ThisActor.
		E. LastActor is Valid & ThisActor is Valid & both are the same Actor - Do Nothing.
	*/

	//if (LastActor == nullptr)
	//{
	//	if (ThisActor != nullptr)
	//	{
	//		/* Scenario B. */
	//		ThisActor->HighlightActor();
	//	}
	//	else
	//	{
	//		/* Both are null, Do Nothing - Case A. */
	//	}
	//}

	//else /* LastActor is Valid. */
	//{
	//	if (ThisActor == nullptr)
	//	{
	//		/* Scenario C. */
	//		LastActor->UnHighlightActor();
	//	}
	//	else /* Both Actors are Valid. */
	//	{
	//		if (LastActor != ThisActor)
	//		{
	//			/* Scenario D. */
	//			LastActor->UnHighlightActor();
	//			ThisActor->HighlightActor();
	//		}
	//		else
	//		{
	//			/* Scenario E. */
	//		}
	//	}
	//}
}

void ARpgPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FRpgGameplayTags::Get().InputTag_LMB))
	{
		bTargetting = ThisActor ? true : false;
		bAutoRunning = false;
	}

	/*GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::Red, *InputTag.ToString());*/
}

void ARpgPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	/*if (GetASC() == nullptr) { return; }

	GetASC()->AbilityInputTagReleased(InputTag);*/

	if (!InputTag.MatchesTagExact(FRpgGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}

		return;
	}

	if (GetASC())
	{
		GetASC()->AbilityInputTagReleased(InputTag);
	}

	if (!bTargetting && !bShiftKeyDown)
	{
		const APawn* ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints();

				for (const FVector& PointLoc : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);

					//DrawDebugSphere(GetWorld(), PointLoc, 10.f, 8, FColor::Green, false, 5.f);
				}

				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
				bAutoRunning = true;
			}
		}

		FollowTime = 0.f;

		bTargetting = false;
	}
	/*GEngine->AddOnScreenDebugMessage(2, 10.f, FColor::Green, *InputTag.ToString());*/
}

void ARpgPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FRpgGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}

		return;
	}

	if (bTargetting || bShiftKeyDown)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();

		if (CursorHit.bBlockingHit)
		{
			CachedDestination = CursorHit.ImpactPoint;
		}

		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();

			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}

	/*GEngine->AddOnScreenDebugMessage(3, 10.f, FColor::Blue, *InputTag.ToString());*/
}

URpgAbilitySystemComponent* ARpgPlayerController::GetASC()
{
	if (RpgAbilitySystemComponent == nullptr)
	{
		RpgAbilitySystemComponent = Cast<URpgAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}

	return RpgAbilitySystemComponent;
}
