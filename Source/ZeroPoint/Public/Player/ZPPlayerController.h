// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ZPPlayerController.generated.h"

class UZPAbilitySystemComponent;
struct FGameplayTag;
class UZPInputConfig;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class ZEROPOINT_API AZPPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	
protected:
	
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;
	
private:
	
	UPROPERTY()
	TObjectPtr<UZPAbilitySystemComponent> ZPAbilitySystemComponent;
	
	UZPAbilitySystemComponent* GetZPAbilitySystemComponent();
	
	/*
	 * Enhanced Input
	 */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LookAction;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	/*
	 * Ability Input
	 */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UZPInputConfig> AbilityInputConfig;
	
	void AbilityInputPressed(FGameplayTag InputTag);
	void AbilityInputReleased(FGameplayTag InputTag);
	void AbilityInputHeld(FGameplayTag InputTag);
	
};
