// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"


// Sets default values
ANPC::ANPC(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProximitySphere"));
	ProxSphere->SetSphereRadius(200.f);
	ProxSphere->AttachTo(RootComponent);
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::Prox);
	NPCMessage = "Hi";
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::Prox_Implementation(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, TEXT("Collision"));
	// If the overlapped actor isn't the player, return
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	// Get the controller
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	// If there is a controller, add the message
	if (PController)
	{
		AMyHUD * hud = Cast<AMyHUD>(PController->GetHUD());
		hud->AddMessage(Message(NPCMessage, 5.f, FColor::White, FColor::Black));
	}
}
