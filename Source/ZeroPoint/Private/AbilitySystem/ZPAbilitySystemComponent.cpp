// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ZPAbilitySystemComponent.h"

#include "AbilitySystem/Abilities/ZPGameplayAbility.h"

void UZPAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UZPAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UZPAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	
}

void UZPAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	if (!IsOwnerActorAuthoritative() || bStartupAbilitiesGiven == true)
	{
		return;
	}
	
	for (auto& StartupAbility : StartupAbilities)
	{
		if (StartupAbility == nullptr) continue;
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(StartupAbility, 1);
		UZPGameplayAbility* ZPStartupAbility = Cast<UZPGameplayAbility>(AbilitySpec.Ability);
		if (ZPStartupAbility)
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(ZPStartupAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
	bStartupAbilitiesGiven = true;
}
