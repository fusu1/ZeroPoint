// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ZPCharacter.h"

#include "AbilitySystem/ZPAbilitySystemComponent.h"
#include "AbilitySystem/ZPAttributeSet.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Player/ZPPlayerState.h"

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
}

void AZPCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}

void AZPCharacter::InitAbilityActorInfo()
{
	AZPPlayerState* ZPPlayerState = CastChecked<AZPPlayerState>(GetPlayerState());
	AbilitySystemComponent = CastChecked<UZPAbilitySystemComponent>(ZPPlayerState->GetAbilitySystemComponent());
	AttributeSet = ZPPlayerState->GetAttributeSet();
	AbilitySystemComponent->InitAbilityActorInfo(ZPPlayerState, this);
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


