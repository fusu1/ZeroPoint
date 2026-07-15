// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "ZPPlayerState.generated.h"

class UZPAttributeSet;
class UZPAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class ZEROPOINT_API AZPPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AZPPlayerState();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UZPAttributeSet* GetAttributeSet() const;
	
protected:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UZPAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UZPAttributeSet> AttributeSet;
	
private:
	
};
