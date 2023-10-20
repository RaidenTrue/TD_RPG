// Copyright by Savvas JRD - LTD Cyprus

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "RpgPlayerController.generated.h"

class UInputAction;
class URpgInputConfig;
class UInputMappingContext;
class IEnemyInterface;

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

	TObjectPtr<IEnemyInterface> LastActor;

	TObjectPtr<IEnemyInterface> ThisActor;

	void AbilityInputTagPressed(FGameplayTag InputTag);

	void AbilityInputTagReleased(FGameplayTag InputTag);

	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<URpgInputConfig> InputConfig;
};
