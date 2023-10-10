// Copyright by Savvas JRD - LTD Cyprus


#include "Player/RpgPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystem/RpgAttributeSet.h"
#include "AbilitySystem/RpgAbilitySystemComponent.h"

ARpgPlayerState::ARpgPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<URpgAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<URpgAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

void ARpgPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARpgPlayerState, Level);
}

UAbilitySystemComponent* ARpgPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ARpgPlayerState::OnRep_Level(int32 PreviousLevel)
{

}
