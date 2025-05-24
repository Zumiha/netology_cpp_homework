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
  WeaponFireRate = this->Weapon->getFireRate();
  FireMode = WeaponFireMode::E_SingleFire;

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


void ULMAWeaponComponent::FireStart() {
    if (Weapon && !AnimReloading) {
        bIsShooting = true;    
        WeaponFire();
    }
}

void ULMAWeaponComponent::FireStop() {
    bIsShooting = false;
    GetWorld()->GetTimerManager().ClearTimer(FireTimer);
}

void ULMAWeaponComponent::WeaponFire() {
    if (bIsShooting) {
        Weapon->Fire();
        if (FireMode == WeaponFireMode::E_FullAuto) {
            GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &ULMAWeaponComponent::WeaponFire, WeaponFireRate, true);
        }
    }
}

void ULMAWeaponComponent::Reload() {
    if (CantReload()) {
        //UE_LOG(LogTemp, Display, TEXT("Can't reload!"));
        return;
    }
    FireStop();
    AnimReloading = true;
    Weapon->ChangeClip();
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    Character->PlayAnimMontage(ReloadMontage);
    //UE_LOG(LogTemp, Display, TEXT("Reload montage launched"));
}

void ULMAWeaponComponent::ChangeFireMode() {
    FireStop();
    switch (FireMode) {
  
    case WeaponFireMode::E_SingleFire: 
        FireMode = WeaponFireMode::E_FullAuto;
        UE_LOG(LogTemp, Display, TEXT("Firemode FullAuto"));
        break;    
    case WeaponFireMode::E_FullAuto:
        FireMode = WeaponFireMode::E_SingleFire;
        UE_LOG(LogTemp, Display, TEXT("Firemode Sigle Shot"));
        break;
    }
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

bool ULMAWeaponComponent::CantReload() const { 
    //auto WeCanRealod = !AnimReloading || !Weapon->IsCurrentClipFull();
    // 
    UE_LOG(LogTemp, Display, TEXT("Reload Animation: %s"), *FString::FromInt(!AnimReloading));
    UE_LOG(LogTemp, Display, TEXT("Clip is Full: %s"), *FString::FromInt(Weapon->IsCurrentClipFull()));

    return AnimReloading || Weapon->IsCurrentClipFull();
}
