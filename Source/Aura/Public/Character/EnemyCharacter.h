// Copyright by Savvas JRD - LTD Cyprus

#pragma once

#include "CoreMinimal.h"
#include "Character/RpgBaseCharacter.h"
#include "Interfaces/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AEnemyCharacter : public ARpgBaseCharacter, public IEnemyInterface
{
	GENERATED_BODY()
	
public:

	AEnemyCharacter();

	/* EnemyInterface. */
	virtual void HighlightActor() override;

	virtual void UnHighlightActor() override;
	/* End EnemyInterface. */

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

protected:

	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;
};
