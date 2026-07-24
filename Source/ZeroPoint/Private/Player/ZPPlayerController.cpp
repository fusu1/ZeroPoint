// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ZPPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "AbilitySystem/ZPAbilitySystemComponent.h"
#include "Engine/Engine.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Pawn.h"
#include "Input/ZPInputComponent.h"
#include "Player/ZPPlayerState.h"

void AZPPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void AZPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UZPInputComponent* ZPInputComponent = CastChecked<UZPInputComponent>(InputComponent);
	ZPInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	ZPInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	ZPInputComponent->BindAbilityActions(AbilityInputConfig, this, &ThisClass::AbilityInputPressed, &ThisClass::AbilityInputReleased, &ThisClass::AbilityInputHeld);
}

UZPAbilitySystemComponent* AZPPlayerController::GetZPAbilitySystemComponent()
{
	if (!ZPAbilitySystemComponent)
	{
		AZPPlayerState* ZPPlayerState = GetPlayerState<AZPPlayerState>();
		if (ZPPlayerState)
		{
			UZPAbilitySystemComponent* ZPASC = Cast<UZPAbilitySystemComponent>(ZPPlayerState->GetAbilitySystemComponent());
			if (ZPASC)
			{
				ZPAbilitySystemComponent = ZPASC;
				return ZPAbilitySystemComponent;
			}
		}
	}
	else
	{
		return ZPAbilitySystemComponent;
	}
	return nullptr;
}

void AZPPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.f);
	
	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if (APawn* ControllerPawn = GetPawn())
	{
		ControllerPawn->AddMovementInput(ForwardVector, InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightVector, InputAxisVector.X);
	}
}

void AZPPlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void AZPPlayerController::AbilityInputPressed(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("Pressed"));
	
	if (GetZPAbilitySystemComponent() == nullptr) return;
	
	ZPAbilitySystemComponent->AbilityInputTagPressed(InputTag);
}

void AZPPlayerController::AbilityInputReleased(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("Released"));
	
	if (GetZPAbilitySystemComponent() == nullptr) return;
	
	ZPAbilitySystemComponent->AbilityInputTagReleased(InputTag);
}

void AZPPlayerController::AbilityInputHeld(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("Held"));
	
	if (GetZPAbilitySystemComponent() == nullptr) return;
	
	ZPAbilitySystemComponent->AbilityInputTagHeld(InputTag);
}
