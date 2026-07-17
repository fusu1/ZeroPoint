// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/ZPHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/ZPUserWidget.h"
#include "UI/WidgetController/ZPWidgetController.h"
#include "UI/WidgetController/ZPOverlayWidgetController.h"

void AZPHUD::InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState,
                         UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet)
{
	check(OverlayWidgetClass);
	check(OverlayWidgetControllerClass);
	OverlayWidget = CreateWidget<UZPUserWidget>(PlayerController, OverlayWidgetClass);
	
	const FWidgetControllerParams OverlayWidgetControllerParams(PlayerController, PlayerState, AbilitySystemComponent, AttributeSet);
	GetOverlayWidgetController(OverlayWidgetControllerParams);
	
	OverlayWidget->SetWidgetController(OverlayWidgetController);
	
	OverlayWidgetController->BroadcastInitialValues();
	
	OverlayWidget->AddToViewport();
}

UZPOverlayWidgetController* AZPHUD::GetOverlayWidgetController(
	const FWidgetControllerParams& OverlayWidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UZPOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(OverlayWidgetControllerParams);
		OverlayWidgetController->BindCallbacksToDependencies();
		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}
