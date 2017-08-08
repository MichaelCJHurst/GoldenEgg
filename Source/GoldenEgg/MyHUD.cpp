// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"

void AMyHUD::DrawMessages()
{
	// Draw some text, to check it works
	// DrawText("Here is some text", FLinearColor::White, 10, 10, hudFont);
	// Iterate from the back to the front of the list, so if an item times out, there
	// won't be any issues
	for (int c = messages.Num() - 1; c >= 0; c--)
	{
		// Draw the background box the right size for the message
		float outputWidth, outputHeight, pad = 10.f;
		GetTextSize(messages[c].message, outputWidth, outputHeight, hudFont, 1.f);

		float messageH = outputHeight + 2.f * pad;
		float x = 0.f, y = c * messageH;
		// Draw the texture, if there is one
		if (messages[c].tex)
		{
			DrawTexture(messages[c].tex, x, y, messageH, messageH, 0, 0, 1, 1);
		}
		else
		{
			DrawRect(FLinearColor::Red, x, y, messageH, messageH);
		}
		x += messageH;
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

void AMyHUD::DrawHUD()
{
	// Call the superclass first
	Super::DrawHUD();
	// Update the screen dimensions
	dims.X = Canvas->SizeX;
	dims.Y = Canvas->SizeY;
	// Draw the messages and health bar
	DrawMessages();
	DrawHealthBar();
}

void AMyHUD::DrawHealthBar()
{
	// Draw the healthbar.
	AAvatar *avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	float barWidth = 200, barHeight = 50, barPad = 12, barMargin = 50;
	float percHp = avatar->Health / avatar->MaxHealth;
	DrawRect(FLinearColor(0, 0, 0, 1), Canvas->SizeX - barWidth - barPad - barMargin,
		Canvas->SizeY - barHeight - barPad - barMargin, barWidth + 2 * barPad, barHeight + 2 * barPad);
	DrawRect(FLinearColor(1 - percHp, percHp, 0, 1), Canvas->SizeX - barWidth - barMargin,
		Canvas->SizeY - barHeight - barMargin, barWidth*percHp, barHeight);
}

void AMyHUD::AddMessage(Message msg)
{
	messages.Add(msg);
}