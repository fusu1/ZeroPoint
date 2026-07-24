// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "ZPInputConfig.h"
#include "ZPInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class ZEROPOINT_API UZPInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(
		const UZPInputConfig* InputConfig,
		UserClass* User,
		PressedFuncType PressedFunc,
		ReleasedFuncType ReleasedFunc,
		HeldFuncType HeldFunc
	);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UZPInputComponent::BindAbilityActions(const UZPInputConfig* InputConfig, UserClass* User,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);
	for (const FZPInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputTag.IsValid() && Action.InputAction != nullptr)
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, User, PressedFunc, Action.InputTag);
			}
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, User, ReleasedFunc, Action.InputTag);
			}
			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, User, HeldFunc, Action.InputTag);
			}
		}
	}
}
