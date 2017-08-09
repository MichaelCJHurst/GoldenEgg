// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupItem.h"


// Sets default values
APickupItem::APickupItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set the default values
	Name = "UNKNOWN ITEM";
	Quantity = 0;
	// Initialize the sphere and mesh
	ProxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	// Make the root object the mesh
	RootComponent = Mesh;
	Mesh->SetSimulatePhysics(true);
	// Collision event for the mesh
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::Prox);
	ProxSphere->AttachTo(Mesh);
	ProxSphere->SetSphereRadius(200.f);
}

// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupItem::Prox_Implementation(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// If the overlapped actor isn't the player, return
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	// Get a reference to the player, in order to give the item
	AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	// Let the player pick this item up
	avatar->Pickup(Name, Quantity, Icon);
	// Get a reference to the controller
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	// Get a reference to the hud
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
	hud->AddMessage(Message(Icon, FString("Picked up ") + FString::FromInt(Quantity) + FString(" ") + Name, 5.f, FColor::White, FColor::Black));
	// Destroy this item, as it was picked up
	Destroy();
}
