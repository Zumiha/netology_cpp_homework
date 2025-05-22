// LeaveMeAlone Game by Netology. All Rights Reserved.


#include "LMAWeaponComponent.h"

#include "GameFramework/Character.h"

#include "LeaveMeAlone/Weapons/LMABaseWeapon.h"
#include "LeaveMeAlone/Animations/LMAReloadFinishedAnimNotify.h"



// Sets default values for this component's properties
ULMAWeaponComponent::ULMAWeaponComponent()
{
	// Set this component to be initialized sahen the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULMAWeaponComponent::BeginPlay() {
	Super::BeginPlay();

	SpawnWeapon();
    InitAnimNotify();	
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
  if (Weapon && !AnimReloading) {
    Weapon->Fire();
  } 
}

void ULMAWeaponComponent::Reload() {
    if (!CanReload()) {
        //UE_LOG(LogTemp, Display, TEXT("Can't reload!"));
        return;
    }
    AnimReloading = true;
    Weapon->ChangeClip();
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    Character->PlayAnimMontage(ReloadMontage);
    //UE_LOG(LogTemp, Display, TEXT("Reload montage launched"));
}

void ULMAWeaponComponent::InitAnimNotify() {
    if (!ReloadMontage) return;
    const auto NotifiesEvents = ReloadMontage->Notifies;
    for (auto NotifyEvent : NotifiesEvents) {
        auto ReloadFinish = Cast<ULMAReloadFinishedAnimNotify>(NotifyEvent.Notify);
        if (ReloadFinish) {
            ReloadFinish->OnNotifyReloadFinished.AddUObject(this, &ULMAWeaponComponent::OnNotifyReloadFinished);
            break;
        }
    }
}

void ULMAWeaponComponent::OnNotifyReloadFinished(USkeletalMeshComponent *SkeletalMesh) {
  const auto Character = Cast<ACharacter>(GetOwner());
  if (Character->GetMesh() == SkeletalMesh) {
      AnimReloading = false;
  }
}

bool ULMAWeaponComponent::CanReload() const { 
    return !AnimReloading; 
}
