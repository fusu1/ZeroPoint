// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ZPCharacter.h"

#include "AbilitySystem/ZPAbilitySystemComponent.h"
#include "AbilitySystem/ZPAttributeSet.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Player/ZPPlayerState.h"
#include "GameplayEffect.h"
#include "Player/ZPPlayerController.h"
#include "UI/HUD/ZPHUD.h"

AZPCharacter::AZPCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	/*
	 * Components
	 */
	GetMesh()->SetOwnerNoSee(true);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(RootComponent);
	
	ArmSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmSkeletalMesh"));
	ArmSkeletalMeshComponent->SetupAttachment(CameraComponent);
	ArmSkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ArmSkeletalMeshComponent->SetOnlyOwnerSee(true);
	
	WeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	WeaponComponent->SetupAttachment(ArmSkeletalMeshComponent, FName("WeaponSocket"));
	WeaponComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponComponent->SetOnlyOwnerSee(true);
}

void AZPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AZPCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	InitAbilityActorInfo();
	InitializeDefaultAttributes();
	InitHUD();
}

void AZPCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
	InitHUD();
}

void AZPCharacter::InitAbilityActorInfo()
{
	AZPPlayerState* ZPPlayerState = CastChecked<AZPPlayerState>(GetPlayerState());
	AbilitySystemComponent = CastChecked<UZPAbilitySystemComponent>(ZPPlayerState->GetAbilitySystemComponent());
	AttributeSet = ZPPlayerState->GetAttributeSet();
	AbilitySystemComponent->InitAbilityActorInfo(ZPPlayerState, this);
}

void AZPCharacter::InitializeDefaultAttributes() const
{
	check(AbilitySystemComponent);
	check(DefaultAttributeEffect);
	
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1.f, ContextHandle);
	if (EffectSpecHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}

void AZPCharacter::InitHUD()
{
	AZPPlayerState* ZPPlayerState = Cast<AZPPlayerState>(GetPlayerState());
	AZPPlayerController* ZPPlayerController = Cast<AZPPlayerController>(Controller);
	if (ZPPlayerController && ZPPlayerState)
	{
		AZPHUD* ZPHUD = Cast<AZPHUD>(ZPPlayerController->GetHUD());
		if (ZPHUD)
		{
			ZPHUD->InitOverlay(ZPPlayerController, ZPPlayerState, GetAbilitySystemComponent(), GetAttributeSet());
		}
	}
}

void AZPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AZPCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UZPAttributeSet* AZPCharacter::GetAttributeSet() const
{
	return AttributeSet;
}


