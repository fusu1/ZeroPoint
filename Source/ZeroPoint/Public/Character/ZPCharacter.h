// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "ZPCharacter.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UZPAttributeSet;
class UZPAbilitySystemComponent;
class UCameraComponent;

UCLASS()
class ZEROPOINT_API AZPCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AZPCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UZPAttributeSet* GetAttributeSet() const;
	
protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/*
	 * GAS
	 */
	UPROPERTY()
	TObjectPtr<UZPAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UZPAttributeSet> AttributeSet;
	
	void InitAbilityActorInfo();
	void InitializeDefaultAttributes() const;
	void InitHUD();
	void AddCharacterStartupAbilities();
private:
	/*
	 * Components
	 */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> ArmSkeletalMeshComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> WeaponComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Attribute")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;
	
	/*
	 * Abilities
	 */
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
