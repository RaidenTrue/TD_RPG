// Copyright by Savvas JRD - LTD Cyprus


#include "AbilitySystem/RpgAbilitySystemLibrary.h"
#include "UI/WidgetController/RpgWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "Kismet/GameplayStatics.h"
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
