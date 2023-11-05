// Copyright by Savvas JRD - LTD Cyprus


#include "Character/EnemyCharacter.h"
#include "RpgGameplayTags.h"
#include "Components/WidgetComponent.h"
#include "AbilitySystem/RpgAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/RpgAbilitySystemLibrary.h"
#include "UI/Widget/RpgUserWidget.h"
#include "AbilitySystem/RpgAbilitySystemComponent.h"
#include "Aura/Aura.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<URpgAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<URpgAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
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

void AEnemyCharacter::Killed()
{
	SetLifeSpan(LifeSpan);

	Super::Killed();
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;

	InitAbilityActorInfo();

	if (HasAuthority())
	{
		URpgAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent);
	}

	if (URpgUserWidget* RpgUserWidget = Cast<URpgUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		RpgUserWidget->SetWidgetController(this);
	}

	if (const URpgAttributeSet* RpgAS = CastChecked<URpgAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RpgAS->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RpgAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

		AbilitySystemComponent->RegisterGameplayTagEvent(FRpgGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&AEnemyCharacter::HitReactTagChanged
		);

		OnHealthChanged.Broadcast(RpgAS->GetHealth());
		OnMaxHealthChanged.Broadcast(RpgAS->GetMaxHealth());
	}
}

void AEnemyCharacter::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;

	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
}

void AEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	Cast<URpgAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
}

void AEnemyCharacter::InitializeDefaultAttributes() const
{
	URpgAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}
