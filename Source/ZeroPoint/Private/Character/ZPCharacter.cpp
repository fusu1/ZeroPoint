// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ZPCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"

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

void AZPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

