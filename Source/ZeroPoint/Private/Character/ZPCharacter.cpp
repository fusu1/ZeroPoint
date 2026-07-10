// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ZPCharacter.h"

#include "Camera/CameraComponent.h"

AZPCharacter::AZPCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	/*
	 * Components
	 */
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(RootComponent);
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

