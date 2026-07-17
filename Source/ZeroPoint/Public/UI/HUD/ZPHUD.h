// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ZPHUD.generated.h"

class APlayerState;
class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;
class UZPAttributeSet;
class UZPAbilitySystemComponent;
class AZPPlayerState;
class AZPPlayerController;
class UZPOverlayWidgetController;
class UZPUserWidget;
/**
 * 
 */
UCLASS()
class ZEROPOINT_API AZPHUD : public AHUD
{
	GENERATED_BODY()
public:
	void InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState, 
		UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet);
	
	UZPOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& OverlayWidgetControllerParams);
	
protected:
	UPROPERTY()
	TObjectPtr<UZPUserWidget> OverlayWidget;
	
	UPROPERTY(EditAnywhere, Category="Widget")
	TSubclassOf<UZPUserWidget> OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UZPOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere, Category="Widget")
	TSubclassOf<UZPOverlayWidgetController> OverlayWidgetControllerClass;
private:
	
};
