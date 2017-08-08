// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Runtime/Engine/Classes/Engine/Canvas.h"
#include "MyHUD.generated.h"

struct Message
{
	FString message;
	float time;
	FColor fontColour;
	FColor backColour;

	Message()
	{
		// Set the defaults
		message = "This is a message";
		time = 5.f;
		fontColour = FColor::White;
		backColour = FColor::Black;
	}

	Message(FString iMessage, float iTime, FColor iFontColour, FColor iBackColour)
	{
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
	// Add a message
	void AddMessage(Message msg);
	// Draw to the HUD
	virtual void DrawHUD() override;
};
