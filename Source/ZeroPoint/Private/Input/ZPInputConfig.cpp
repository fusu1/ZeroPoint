// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ZPInputConfig.h"

#include "InputAction.h"

const UInputAction* UZPInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const FZPInputAction& Info : AbilityInputActions)
	{
		if (Info.InputTag.MatchesTagExact(InputTag) && Info.InputAction != nullptr)
		{
			return Info.InputAction;
		}
	}
	return nullptr;
}
