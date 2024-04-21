// Copyright by Savvas JRD - LTD Cyprus


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/RpgAbilitySystemComponent.h"
//#include "AbilitySystem/Data/AbilityInfo.h"
#include "AbilitySystem/RpgAttributeSet.h"
#include "Player/RpgPlayerState.h"
#include "AbilitySystem/Data/LevelUpInfo.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const URpgAttributeSet* RpgAttributeSet = CastChecked<URpgAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(RpgAttributeSet->GetHealth());

	OnMaxHealthChanged.Broadcast(RpgAttributeSet->GetMaxHealth());

	OnManaChanged.Broadcast(RpgAttributeSet->GetMana());

	OnMaxManaChanged.Broadcast(RpgAttributeSet->GetMaxMana());


}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	ARpgPlayerState* RpgPlayerState = CastChecked<ARpgPlayerState>(PlayerState);
	RpgPlayerState->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);

	const URpgAttributeSet* RpgAttributeSet = CastChecked<URpgAttributeSet>(AttributeSet);

	/* Refactored Implementation with Lambdas - No FunctionCallback. */

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RpgAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RpgAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RpgAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RpgAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);

	if (URpgAbilitySystemComponent* RpgASC = Cast<URpgAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (RpgASC->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(RpgASC);
		}
		else
		{
			RpgASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartupAbilities);
		}

		RpgASC->EffectAssetTags.AddLambda([this](const FGameplayTagContainer& AssetTags)
			{
				for (const FGameplayTag& Tag : AssetTags)
				{
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));

					if (Tag.MatchesTag(MessageTag))
					{
						const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);

						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				}
			}
		);
	}
}

void UOverlayWidgetController::OnInitializeStartupAbilities(URpgAbilitySystemComponent* RpgAbilitySystemComponent)
{
	/* TODO: Get Information about all given Abilities, look up their AbilityInfo & Broadcast it to Widgets. */

	if (!RpgAbilitySystemComponent->bStartupAbilitiesGiven) { return; }

	FForEachAbility BroadcastDelegate;

	BroadcastDelegate.BindLambda([this, RpgAbilitySystemComponent](const FGameplayAbilitySpec& AbilitySpec)
	{
			/* TODO: Need a way to figure out the AbilityTag for a given AbilitySpec. */
			FRpgAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(RpgAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));

			Info.InputTag = RpgAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);

			AbilityInfoDelegate.Broadcast(Info);
	});

	RpgAbilitySystemComponent->ForEachAbility(BroadcastDelegate);
}

void UOverlayWidgetController::OnXPChanged(int32 NewXP) const
{
	const ARpgPlayerState* RpgPlayerState = CastChecked<ARpgPlayerState>(PlayerState);
	const ULevelUpInfo* LevelUpInfo = RpgPlayerState->LevelUpInfo;

	checkf(LevelUpInfo, TEXT("Unable to find LevelUpInfo. Please fill out RpgPlayerState Blueprint."));
	
	const int32 Level = LevelUpInfo->FindLevelForXP(NewXP);
	const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num();

	if (Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[Level].LevelUpRequirement;
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInformation[Level - 1].LevelUpRequirement;

		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;

		const float XPBarPercent = static_cast<float>(XPForThisLevel) / (DeltaLevelRequirement);

		OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
	}
}
