// Fill out your copyright notice in the Description page of Project Settings.

#include "Avatar.h"


// Sets default values
AAvatar::AAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Defaults for the values of health
	Health = MaxHealth = 100;
}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Bind the mouse movement
	InputComponent->BindAxis("Pitch", this, &AAvatar::Pitch);
	InputComponent->BindAxis("Yaw", this, &AAvatar::Yaw);
	// Bind the keyboard movement
	InputComponent->BindAxis("Forward", this, &AAvatar::MoveForward);
	InputComponent->BindAxis("Backward", this, &AAvatar::MoveBackward);
	InputComponent->BindAxis("Left", this, &AAvatar::MoveLeft);
	InputComponent->BindAxis("Right", this, &AAvatar::MoveRight);
}

// Pitch
void AAvatar::Pitch(float amount)
{
	AddControllerYawInput(200.f * amount * GetWorld()->GetDeltaSeconds());
}

// Yaw
void AAvatar::Yaw(float amount)
{
	AddControllerPitchInput(200.f * amount * GetWorld()->GetDeltaSeconds());
}

// Forward movement
void AAvatar::MoveForward(float amount)
{
	// Only enter if there is a controller, and there is an amount
	if (Controller && amount) {
		FVector forwards = GetActorForwardVector();
		AddMovementInput(forwards, amount);
	}
}

// Backwards movement
void AAvatar::MoveBackward(float amount)
{
	if (Controller && amount) {
		FVector backwards = -GetActorForwardVector();
		AddMovementInput(backwards, amount);
	}
}

// Left movement
void AAvatar::MoveLeft(float amount)
{
	if (Controller && amount) {
		FVector backwards = -GetActorRightVector();
		AddMovementInput(backwards, amount);
	}
}

// Right movement
void AAvatar::MoveRight(float amount)
{
	if (Controller && amount) {
		FVector backwards = GetActorRightVector();
		AddMovementInput(backwards, amount);
	}
}
