// Copyright by Savvas JRD - LTD Cyprus


#include "Character/EnemyCharacter.h"
#include "AbilitySystem/RpgAttributeSet.h"
#include "AbilitySystem/RpgAbilitySystemComponent.h"
#include "Aura/Aura.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<URpgAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<URpgAttributeSet>("AttributeSet");
}

void AEnemyCharacter::HighlightActor()
{
	/* Added for Debugging Purposes. Enable to if needed. */
	/*bHighlighted = true;*/

	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AEnemyCharacter::UnHighlightActor()
{
	/* Added for Debugging Purposes. Enable to if needed. */
	/*bHighlighted = false;*/

	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 AEnemyCharacter::GetPlayerLevel()
{
	return Level;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo();
}

void AEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	Cast<URpgAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}
