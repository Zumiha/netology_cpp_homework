// LeaveMeAlone Game by Netology. All Rights Reserved.


#include "LMAWeaponComponent.h"

#include "GameFramework/Character.h"
#include "LeaveMeAlone/Weapons/LMABaseWeapon.h"



// Sets default values for this component's properties
ULMAWeaponComponent::ULMAWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULMAWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	
}


// Called every frame
void ULMAWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULMAWeaponComponent::SpawnWeapon() {
  this->Weapon = GetWorld()->SpawnActor<ALMABaseWeapon>(WeaponClass);

  //if (!Weapon) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Cyan, FString::Printf(TEXT("No weapon!")));
  
  if (Weapon) {
    const auto Character = Cast<ACharacter>(GetOwner());
	if (Character) {
	  //if (!Character) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Cyan, FString::Printf(TEXT("No character!")));
      FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
      Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules,"r_Weapon_Socket");
    }  
  }
}

void ULMAWeaponComponent::Fire() {
  if (Weapon) {
    Weapon->Fire();
  } 
}