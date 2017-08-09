// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyHUD.h"
#include "Components/InputComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Avatar.generated.h"

UCLASS()
class GOLDENEGG_API AAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAvatar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Health and the MaxHealth
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
		float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
		float MaxHealth;
	// A map for the player's backpack
	TMap<FString, int> Backpack;
	// The icons for the items in the backpack
	TMap<FString, UTexture2D*> Icons;
	// A flag for if the inventory is showing
	bool inventoryShowing;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Toggles the inventory
	void ToggleInventory();
	// If the mouse button is clicked
	void MouseClicked();
	// Member function for letting the player pick an item up
	void Pickup(FString Name, int32 Quantity, UTexture2D* Icon);
	// mouse movement
	void Pitch(float amount);
	void Yaw(float yaw);
	// keyboard movement
	void MoveForward(float amount);
	void MoveBackward(float amount);
	void MoveLeft(float amount);
	void MoveRight(float amount);
};
