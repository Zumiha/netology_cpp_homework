// LeaveMeAlone Game by Netologiya. All Rights Reserved.


#include "LMABaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeapon, All, All);

ALMABaseWeapon::ALMABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	SetRootComponent(WeaponMesh);
}

void ALMABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmoWeapon = AmmoWeapon;
}

void ALMABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALMABaseWeapon::Fire() {
	if (CurrentAmmoWeapon.Bullets > 0) {    
		Shoot();
	}
	else {

	}
}

void ALMABaseWeapon::Shoot()
{
	const FTransform SocketTransform = WeaponMesh->GetSocketTransform("Muzzle");
	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceDistance;
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Black, false, 1.0f, 0, 2.0f);

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);

	if (HitResult.bBlockingHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 24, FColor::Red, false, 1.0f);
	}

	DecrementBullets();
}

void ALMABaseWeapon::ChangeClip()
{
	CurrentAmmoWeapon.Bullets = AmmoWeapon.Bullets;
	AmmoWeaponChange.Broadcast(CurrentAmmoWeapon.Bullets, AmmoWeapon.Bullets);
}

int ALMABaseWeapon::GetAmmo(AmmoOption AmmoOption) { 
	if (AmmoOption == AmmoOption::Current) {
  		return this->CurrentAmmoWeapon.Bullets;
	}
	else if (AmmoOption == AmmoOption::Max) {
        return this->AmmoWeapon.Bullets;
	}
	return 0;
}

void ALMABaseWeapon::DecrementBullets()
{
	CurrentAmmoWeapon.Bullets--;	
	AmmoWeaponChange.Broadcast(CurrentAmmoWeapon.Bullets, AmmoWeapon.Bullets);

	//UE_LOG(LogWeapon, Display, TEXT("Bullets = %s"), *FString::FromInt(CurrentAmmoWeapon.Bullets));

	if (IsCurrentClipEmpty())
	{
		WeapopnNeedReload.Broadcast();
	}
	
}