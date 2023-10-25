// Copyright by Savvas JRD - LTD Cyprus

#pragma once

#include "CoreMinimal.h"
#include "Character/RpgBaseCharacter.h"
#include "Interfaces/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "EnemyCharacter.generated.h"

class UWidgetComponent;

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

	/* Begin Combat Interface. */

	virtual int32 GetPlayerLevel() override;

	/* End Combat Interface. */

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

protected:

	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Class Defaults")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

private:

};
