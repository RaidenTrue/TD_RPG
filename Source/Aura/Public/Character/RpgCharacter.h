// Copyright by Savvas JRD - LTD Cyprus

#pragma once

#include "CoreMinimal.h"
#include "Character/RpgBaseCharacter.h"
#include "RpgCharacter.generated.h"

class ARpgPlayerState;
class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class AURA_API ARpgCharacter : public ARpgBaseCharacter
{
	GENERATED_BODY()

public:

	ARpgCharacter();

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

protected:


private:

	void InitAbilityActorInfo();

	TObjectPtr<ARpgPlayerState> PlayerState;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> PlayerCamera;
};
