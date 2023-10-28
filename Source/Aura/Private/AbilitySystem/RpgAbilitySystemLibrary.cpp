// Copyright by Savvas JRD - LTD Cyprus


#include "AbilitySystem/RpgAbilitySystemLibrary.h"
#include "UI/WidgetController/RpgWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Game/RpgGameModeBase.h"
#include "Player/RpgPlayerState.h"
#include "UI/HUD/RpgHUD.h"

UOverlayWidgetController* URpgAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ARpgHUD* RpgHUD = Cast<ARpgHUD>(PC->GetHUD()))
		{
			ARpgPlayerState* PS = PC->GetPlayerState<ARpgPlayerState>();

			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();

			UAttributeSet* AS = PS->GetAttributeSet();

			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);

			return RpgHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}

	return nullptr;
}

UAttributeMenuWidgetController* URpgAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ARpgHUD* RpgHUD = Cast<ARpgHUD>(PC->GetHUD()))
		{
			ARpgPlayerState* PS = PC->GetPlayerState<ARpgPlayerState>();

			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();

			UAttributeSet* AS = PS->GetAttributeSet();

			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);

			return RpgHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}

	return nullptr;
}

void URpgAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	ARpgGameModeBase* RpgGameMode = Cast<ARpgGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));

	if (RpgGameMode == nullptr) { return; }

	AActor* AvatarActor = ASC->GetAvatarActor();

	UCharacterClassInfo* CharacterClassInfo = RpgGameMode->CharacterClassInfo;
	FCharacterClassDefaultInfo ClassDefaultInfo = RpgGameMode->CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);

	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);

	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);

	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}
