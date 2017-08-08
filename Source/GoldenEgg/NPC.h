// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Avatar.h"
#include "GameModeGoldenEgg.h"
#include "MyHUD.h"
#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

UCLASS()
class GOLDENEGG_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// NPC's image
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
		UTexture2D* Face;
	// The name of this NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
		FString NPCName;
	// The NPC message
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
		FString NPCMessage;
	// Proximity sphere
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
		class USphereComponent* ProxSphere;
	// Triggered when the sphere is messed with
	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
		void Prox(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
