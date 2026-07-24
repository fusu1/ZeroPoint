// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ZPAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class ZEROPOINT_API UZPAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	
	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	
private:
	bool bStartupAbilitiesGiven = false;
};
