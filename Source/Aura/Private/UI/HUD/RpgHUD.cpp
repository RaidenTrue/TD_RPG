// Copyright by Savvas JRD - LTD Cyprus


#include "UI/HUD/RpgHUD.h"
#include "UI/Widget/RpgUserWidget.h"

void ARpgHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);

	Widget->AddToViewport();
}
