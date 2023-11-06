// Copyright by Savvas JRD - LTD Cyprus

#pragma once

#include "CoreMinimal.h"
#include "Character/RpgBaseCharacter.h"
#include "Interfaces/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "EnemyCharacter.generated.h"

class UWidgetComponent;
class ARpgAIController;
class UBehaviorTree;

/**
 * 
 */
UCLASS()
class AURA_API AEnemyCharacter : public ARpgBaseCharacter, public IEnemyInterface
{
	GENERATED_BODY()
	
public:

	AEnemyCharacter();

	virtual void PossessedBy(AController* NewController) override;

	/* EnemyInterface. */
	virtual void HighlightActor() override;

	virtual void UnHighlightActor() override;
	/* End EnemyInterface. */

	/* Begin Combat Interface. */

	virtual int32 GetPlayerLevel() override;
	
	virtual void Killed() override;

	/* End Combat Interface. */

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category = Combat)
	bool bHitReacting = false;
	
	UPROPERTY(BlueprintReadOnly, Category = Combat)
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat)
	float LifeSpan = 5.f;

protected:

	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, Category = "A.I.")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ARpgAIController> RpgAIController;

private:

};
