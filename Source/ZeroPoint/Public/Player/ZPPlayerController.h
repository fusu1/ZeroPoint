// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ZPPlayerController.generated.h"

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
	
	/*
	 * Enhanced Input
	 */
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> InputMappingContext;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> LookAction;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
};
