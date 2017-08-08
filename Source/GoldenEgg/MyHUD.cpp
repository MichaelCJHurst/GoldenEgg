// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"

void AMyHUD::DrawHUD()
{
	// Call the superclass first
	Super::DrawHUD();
	// Draw some text, to check it works
	DrawText("Here is some text", FLinearColor::White, 10, 10, hudFont);
}