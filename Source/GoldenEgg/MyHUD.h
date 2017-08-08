// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

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
	// Draw to the HUD
	virtual void DrawHUD() override;
};
