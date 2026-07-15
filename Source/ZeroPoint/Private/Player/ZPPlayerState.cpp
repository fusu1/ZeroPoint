// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ZPPlayerState.h"

#include "AbilitySystem/ZPAbilitySystemComponent.h"
#include "AbilitySystem/ZPAttributeSet.h"

AZPPlayerState::AZPPlayerState()
{
	NetUpdateFrequency = 100.f;
	
	/*
	 * Ability System Component
	 */
	AbilitySystemComponent = CreateDefaultSubobject<UZPAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	/*
	 * Attribute Set
	 */
	AttributeSet = CreateDefaultSubobject<UZPAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* AZPPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UZPAttributeSet* AZPPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
