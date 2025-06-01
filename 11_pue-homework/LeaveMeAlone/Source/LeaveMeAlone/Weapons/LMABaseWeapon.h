// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMABaseWeapon.generated.h"

class USkeletalMeshComponent;

DECLARE_MULTICAST_DELEGATE(FNoAmmoInClipSignature);
DECLARE_MULTICAST_DELEGATE_TwoParams(FCurrentAmmoSignature, int, int);

enum AmmoOption {
	Current,
	Max
};

USTRUCT(BlueprintType)
struct FAmmoWeapon
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	bool Infinite;
};

UCLASS()
class LEAVEMEALONE_API ALMABaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	ALMABaseWeapon();
		
	void Fire();
	void ChangeClip();

	float getFireRate() { return this->FireRate; };
	int GetAmmo(AmmoOption AmmoOption);

	bool IsCurrentClipEmpty() const {return CurrentAmmoWeapon.Bullets == 0;}
	bool IsCurrentClipFull() const {return CurrentAmmoWeapon.Bullets == AmmoWeapon.Bullets;}

	FNoAmmoInClipSignature WeapopnNeedReload;
	FCurrentAmmoSignature AmmoWeaponChange;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float TraceDistance = 800.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	FAmmoWeapon AmmoWeapon {30, 0, true};	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") 
	float FireRate = 0.08f;

	virtual void BeginPlay() override;

	void Shoot();
	void DecrementBullets();

public:
	virtual void Tick(float DeltaTime) override;

private:
	FAmmoWeapon CurrentAmmoWeapon;
};
