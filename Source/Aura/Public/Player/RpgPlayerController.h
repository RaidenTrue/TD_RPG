// Copyright by Savvas JRD - LTD Cyprus

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "RpgPlayerController.generated.h"

class UInputAction;
class URpgInputConfig;
class USplineComponent;
class UInputMappingContext;
class IEnemyInterface;
class URpgAbilitySystemComponent;

struct FInputActionValue;

/**
 * 
 */
UCLASS()
class AURA_API ARpgPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ARpgPlayerController();

	virtual void PlayerTick(float DeltaTime);

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> RpgContext;
	
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();

	FHitResult CursorHit;

	TObjectPtr<IEnemyInterface> LastActor;

	TObjectPtr<IEnemyInterface> ThisActor;

	void AbilityInputTagPressed(FGameplayTag InputTag);

	void AbilityInputTagReleased(FGameplayTag InputTag);

	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<URpgInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<URpgAbilitySystemComponent> RpgAbilitySystemComponent;

	URpgAbilitySystemComponent* GetASC();


	FVector CachedDestination = FVector::ZeroVector;

	float FollowTime = 0.f;

	float ShortPressThreshold = 0.5f;

	bool bAutoRunning = false;

	bool bTargetting = false;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	void AutoRun();
 };
