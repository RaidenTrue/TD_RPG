// Copyright by Savvas JRD - LTD Cyprus

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "RpgBaseCharacter.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class AURA_API ARpgBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARpgBaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo();

	UPROPERTY(EditAnywhere, Category = Combat)
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//	// Called to bind functionality to input
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
