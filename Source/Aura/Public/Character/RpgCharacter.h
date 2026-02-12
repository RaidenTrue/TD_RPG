// Copyright by Savvas JRD - LTD Cyprus

#pragma once

#include "CoreMinimal.h"
#include "Character/RpgBaseCharacter.h"
#include "Aura/Public/Interfaces/PlayerInterface.h"
#include "RpgCharacter.generated.h"

class ARpgPlayerState;
class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class AURA_API ARpgCharacter : public ARpgBaseCharacter, public IPlayerInterface
{
	GENERATED_BODY()

public:

	ARpgCharacter();

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	/* Player Interface. */

	virtual void AddToXP_Implementation(int32 InXP) override;
	virtual void LevelUp_Implementation() override;

	/* End Player Interface. */

	/* Begin Combat Interface. */

	virtual int32 GetPlayerLevel_Implementation() override;

	/* End Combat Interface. */

protected:


private:

	virtual void InitAbilityActorInfo() override;

	TObjectPtr<ARpgPlayerState> PlayerState;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> PlayerCamera;
};
