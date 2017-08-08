// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Avatar.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Runtime/Engine/Classes/Engine/Canvas.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MyHUD.generated.h"

struct Message
{
	UTexture* tex;
	FString message;
	float time;
	FColor fontColour;
	FColor backColour;

	Message()
	{
		// Set the defaults
		tex = 0;
		message = "This is a message";
		time = 5.f;
		fontColour = FColor::White;
		backColour = FColor::Black;
	}

	Message(FString iMessage, float iTime, FColor iFontColour, FColor iBackColour)
	{
		tex = 0;
		message = iMessage;
		time = iTime;
		fontColour = iFontColour;
		backColour = iBackColour;
	}

	Message(UTexture* iTex, FString iMessage, float iTime, FColor iFontColour, FColor iBackColour)
	{
		tex = iTex;
		message = iMessage;
		time = iTime;
		fontColour = iFontColour;
		backColour = iBackColour;
	}
};
/**
 * 
 */
UCLASS()
class GOLDENEGG_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	// Font for the HUD
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
		UFont* hudFont;
	// An array of messages to display
	TArray<Message> messages;
	// This is for the screen dimensions
	FVector2D dims;
	// Add a message
	void AddMessage(Message msg);
	// Functions for drawing the messages and the health bar
	void DrawMessages();
	void DrawHealthBar();
	// Draw to the HUD
	virtual void DrawHUD() override;
};
