// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ZPInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FZPInputAction
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class ZEROPOINT_API UZPInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FZPInputAction> AbilityInputActions;
};
