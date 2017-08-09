// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Runtime/Engine/Classes/Engine/Canvas.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MyHUD.generated.h"

struct Message
{
	UTexture2D* tex;
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

	Message(UTexture2D* iTex, FString iMessage, float iTime, FColor iFontColour, FColor iBackColour)
	{
		tex = iTex;
		message = iMessage;
		time = iTime;
		fontColour = iFontColour;
		backColour = iBackColour;
	}
};
struct Icon
{
	FString name;
	UTexture2D* tex;

	Icon()
	{
		name = "UNKNOWN ICON";
		tex = 0;
	}

	Icon(FString& iName, UTexture2D* iTex)
	{
		name = iName;
		tex = iTex;
	}
};
struct Widget
{
	Icon icon;
	FVector2D pos, size;
	
	Widget(Icon iIcon)
	{
		icon = iIcon;
	}

	float left()
	{
		return pos.X;
	}

	float right()
	{
		return pos.X + size.X;
	}

	float top()
	{
		return pos.Y;
	}

	float bottom()
	{
		return pos.Y + size.Y;
	}

	bool hit(FVector2D p)
	{
		return p.X > left() && p.X < right() && p.Y > top() && p.Y < bottom();
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
	// The held widget
	Widget* heldWidget;
	// An array of messages to display
	TArray<Message> messages;
	TArray<Widget> widgets;
	// This is for the screen dimensions
	FVector2D dims;
	// When the mouse is clicked
	void MouseClicked();
	void MouseMoved();
	// Add a message and widget
	void AddMessage(Message msg);
	void AddWidget(Widget widget);
	// Functions for drawing the messages and the health bar
	void DrawMessages();
	void DrawHealthBar();
	void DrawWidgets();
	// Draw to the HUD
	virtual void DrawHUD() override;
};
