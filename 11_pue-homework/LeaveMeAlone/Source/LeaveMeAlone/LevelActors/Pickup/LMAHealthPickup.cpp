// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#include "LeaveMeAlone/LevelActors/Pickup/LMAHealthPickup.h"
#include "LeaveMeAlone/Player/LMADefaultCharacter.h"
#include "LeaveMeAlone/Components/Health/LMAHealthComponent.h"
#include "Components/SphereComponent.h"

ALMAHealthPickup::ALMAHealthPickup() {
  PrimaryActorTick.bCanEverTick = true;

  SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
  SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
  SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
  SetRootComponent(SphereComponent);
}

void ALMAHealthPickup::BeginPlay() { Super::BeginPlay(); }

void ALMAHealthPickup::NotifyActorBeginOverlap(AActor *OtherActor) {    
    Super::NotifyActorBeginOverlap(OtherActor);  
    if (const auto Charcter = Cast<ALMADefaultCharacter>(OtherActor)) {
        if (GivePickup(Charcter)) {
          PickupWasTaken();
        }
    } else {
        return;
    }
}

void ALMAHealthPickup::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

bool ALMAHealthPickup::GivePickup(ALMADefaultCharacter *Character) {
  const auto HealthComponent = Character->GetHealthComponent();
  if (!HealthComponent)
    return false;

  return HealthComponent->AddHealth(HealthFromPickup);
}

void ALMAHealthPickup::PickupWasTaken() {
  SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
  GetRootComponent()->SetVisibility(false, true);

  FTimerHandle RespawnTimerHandle;
  GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ALMAHealthPickup::RespawnPickup, RespawnTime);
}

void ALMAHealthPickup::RespawnPickup() {
  SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
  GetRootComponent()->SetVisibility(true, true);
}