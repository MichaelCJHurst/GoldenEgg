// Fill out your copyright notice in the Description page of Project Settings.

#include "Avatar.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

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
	// Bind mouse clicking
	InputComponent->BindAction("MouseClickedLMB", IE_Pressed, this, &AAvatar::MouseClicked);
	// Bind the inventory stuff
	InputComponent->BindAction("Inventory", IE_Pressed, this, &AAvatar::ToggleInventory);
	// Bind the mouse movement
	InputComponent->BindAxis("Pitch", this, &AAvatar::Pitch);
	InputComponent->BindAxis("Yaw", this, &AAvatar::Yaw);
	// Bind the keyboard movement
	InputComponent->BindAxis("Forward", this, &AAvatar::MoveForward);
	InputComponent->BindAxis("Backward", this, &AAvatar::MoveBackward);
	InputComponent->BindAxis("Left", this, &AAvatar::MoveLeft);
	InputComponent->BindAxis("Right", this, &AAvatar::MoveRight);
}

// Pickup an item
void AAvatar::Pickup(FString Name, int32 Quantity, UTexture2D* Icon)
{
	// If item is already in the inventory, add the quantity
	if (Backpack.Find(Name))
	{
		Backpack[Name] += Quantity;
	}
	// Otherwise add item
	else
	{
		Backpack.Add(Name, Quantity);
		// Add the ref the first time it's picked up
		Icons.Add(Name, Icon);
	}
}

// Inventory
void AAvatar::ToggleInventory()
{
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, "Showing inventory");
	}*/
	// Get the controller and HUD
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
	// If the inventory is displayed, hide it
	if (inventoryShowing)
	{
		hud->widgets.Empty();
		inventoryShowing = false;
		PController->bShowMouseCursor = false;
		return;
	}
	// Otherwise show the inventory
	inventoryShowing = true;
	PController->bShowMouseCursor = true;
	for (TMap<FString, int>::TIterator it = Backpack.CreateIterator(); it; ++it)
	{
		// Combine the string name with the quantity
		FString fs = it->Key + FString::Printf(TEXT(" x %d"), it->Value);
		UTexture2D* tex = 0;
		if (Icons.Find(it->Key))
		{
			tex = Icons[it->Key];
		}
		hud->AddWidget(Widget(Icon(fs, tex)));
	}
}

// If the mouse is clicked
void AAvatar::MouseClicked()
{
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
	hud->MouseClicked();
}

// Pitch
void AAvatar::Pitch(float amount)
{
	if (inventoryShowing)
	{
		// Pass the input to the HUD
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
		hud->MouseMoved();
		return;
	}
	AddControllerYawInput(200.f * amount * GetWorld()->GetDeltaSeconds());
}

// Yaw
void AAvatar::Yaw(float amount)
{
	if (inventoryShowing)
	{
		// Pass the input to the HUD
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
		hud->MouseMoved();
		return;
	}
	AddControllerPitchInput(200.f * amount * GetWorld()->GetDeltaSeconds());
}

// Forward movement
void AAvatar::MoveForward(float amount)
{
	// Only enter if the inventory isn't shown, there is a controller, and there is an amount
	if (!inventoryShowing && Controller && amount) {
		FVector forwards = GetActorForwardVector();
		AddMovementInput(forwards, amount);
	}
}

// Backwards movement
void AAvatar::MoveBackward(float amount)
{
	if (!inventoryShowing && Controller && amount) {
		FVector backwards = -GetActorForwardVector();
		AddMovementInput(backwards, amount);
	}
}

// Left movement
void AAvatar::MoveLeft(float amount)
{
	if (!inventoryShowing && Controller && amount) {
		FVector backwards = -GetActorRightVector();
		AddMovementInput(backwards, amount);
	}
}

// Right movement
void AAvatar::MoveRight(float amount)
{
	if (!inventoryShowing && Controller && amount) {
		FVector backwards = GetActorRightVector();
		AddMovementInput(backwards, amount);
	}
}
