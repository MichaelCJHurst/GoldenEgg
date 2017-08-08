// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"

void AMyHUD::DrawHUD()
{
	// Call the superclass first
	Super::DrawHUD();
	// Draw some text, to check it works
	DrawText("Here is some text", FLinearColor::White, 10, 10, hudFont);
	// Iterate from the back to the front of the list, so if an item times out, there
	// won't be any issues
	for (int c = messages.Num() - 1; c >= 0; c--)
	{
		// Draw the background box the right size for the message
		float outputWidth, outputHeight, pad = 10.f;
		GetTextSize(messages[c].message, outputWidth, outputHeight, hudFont, 1.f);

		float messageH = outputHeight + 2.f * pad;
		float x = 0.f, y = c * messageH;
		// Draw the background
		DrawRect(messages[c].backColour, x, y, Canvas->SizeX, messageH);
		// Draw the message
		DrawText(messages[c].message, messages[c].fontColour, x + pad, y + pad, hudFont);
		// Reduce the lifetime by the delta seconds
		messages[c].time -= GetWorld()->GetDeltaSeconds();
		// If the message has expired, remove it
		if (messages[c].time < 0)
		{
			messages.RemoveAt(c);
		}
	}
}

void AMyHUD::AddMessage(Message msg)
{
	messages.Add(msg);
}