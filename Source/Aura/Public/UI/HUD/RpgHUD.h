// Copyright by Savvas JRD - LTD Cyprus

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RpgHUD.generated.h"

class UAttributeSet;
class URpgUserWidget;
class UAbilitySystemComponent;
class UOverlayWidgetController;
class UAttributeMenuWidgetController;

struct FWidgetControllerParams;

/**
 * 
 */
UCLASS()
class AURA_API ARpgHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

protected:

	/*virtual void BeginPlay() override;*/

private:

	UPROPERTY()
	TObjectPtr<URpgUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<URpgUserWidget> OverlayWidgetClass;

	/* Overlay Widget Controller. */

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	/* Attribute Menu Widget Controller. */

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;

};
