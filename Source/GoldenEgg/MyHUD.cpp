// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "Avatar.h"

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
	DrawWidgets();
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

void AMyHUD::DrawWidgets()
{
	for (int c = 0; c < widgets.Num(); c++)
	{
		DrawTexture(widgets[c].icon.tex, widgets[c].pos.X, widgets[c].pos.Y, widgets[c].size.X, widgets[c].size.Y, 0, 0, 1, 1);
		DrawText(widgets[c].icon.name, FLinearColor::Yellow, widgets[c].pos.X, widgets[c].pos.Y, hudFont, .6f, false);
	}
}

void AMyHUD::AddMessage(Message msg)
{
	messages.Add(msg);
}

void AMyHUD::AddWidget(Widget widget)
{
	// Find the position of the widget based on the grid
	FVector2D start(200, 200), pad(12, 12);
	widget.size = FVector2D(100, 100);
	widget.pos = start;
	// compute the position
	for (int c = 0; c < widgets.Num(); c++)
	{
		// Move the position to the right a bit
		widget.pos.X += widget.size.X + pad.X;
		// If there is no more room to the right, jump to the next line
		if (widget.pos.X + widget.size.X > dims.X)
		{
			widget.pos.X = start.X;
			widget.pos.Y += widget.size.Y + pad.Y;
		}
	}
	// Add the widget
	widgets.Add(widget);
}

void AMyHUD::MouseClicked()
{
	FVector2D mouse;
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	PController->GetMousePosition(mouse.X, mouse.Y);
	heldWidget = NULL;
	// See if the mouse position hits any widgets
	for (int c = 0; c < widgets.Num(); c++)
	{
		if (widgets[c].hit(mouse))
		{
			heldWidget = &widgets[c];
			return;
		}
	}
}

void AMyHUD::MouseMoved()
{
	static FVector2D lastMouse;
	FVector thisMouse, dMouse;
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	PController->GetMousePosition(thisMouse.X, thisMouse.Y);
	dMouse.X = thisMouse.X - lastMouse.X;
	dMouse.Y = thisMouse.Y - lastMouse.Y;
	// If the mouse has been held down for more than 0 seconds
	float time = PController->GetInputKeyTimeDown(EKeys::LeftMouseButton);
	if (time > 0.f && heldWidget)
	{
		// Move the widget by the displacement
		heldWidget->pos.X += dMouse.X;
		heldWidget->pos.Y += dMouse.Y;
	}
	lastMouse.X = thisMouse.X;
	lastMouse.Y = thisMouse.Y;
}
