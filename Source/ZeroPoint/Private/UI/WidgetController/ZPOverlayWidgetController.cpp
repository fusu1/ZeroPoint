// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/ZPOverlayWidgetController.h"

#include "AbilitySystem/ZPAbilitySystemComponent.h"
#include "AbilitySystem/ZPAttributeSet.h"

void UZPOverlayWidgetController::BroadcastInitialValues()
{
	UZPAttributeSet* ZPAttributeSet = CastChecked<UZPAttributeSet>(AttributeSet);
	
	OnHealthChangedDelegate.Broadcast(ZPAttributeSet->GetHealth());
	OnMaxHealthChangedDelegate.Broadcast(ZPAttributeSet->GetMaxHealth());
}

void UZPOverlayWidgetController::BindCallbacksToDependencies()
{
	UZPAbilitySystemComponent* ZPAbilitySystemComponent = CastChecked<UZPAbilitySystemComponent>(AbilitySystemComponent);
	UZPAttributeSet* ZPAttributeSet = CastChecked<UZPAttributeSet>(AttributeSet);
	
	ZPAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ZPAttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
	ZPAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ZPAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ThisClass::OnMaxHealthChanged);
	
}

void UZPOverlayWidgetController::OnHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChangedDelegate.Broadcast(Data.NewValue);
}

void UZPOverlayWidgetController::OnMaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChangedDelegate.Broadcast(Data.NewValue);
}
