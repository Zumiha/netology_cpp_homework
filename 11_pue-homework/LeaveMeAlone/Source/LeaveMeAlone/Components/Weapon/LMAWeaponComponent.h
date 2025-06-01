// LeaveMeAlone Game by Netology. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAWeaponComponent.generated.h"

class ALMABaseWeapon;
class UAnimMontage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAmmoValueChange, int, Bullets, int, MaxBullets);

enum WeaponFireMode {
	E_SingleFire,
	E_FullAuto
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEAVEMEALONE_API ULMAWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULMAWeaponComponent();

    UPROPERTY()
    ALMABaseWeapon *Weapon = nullptr;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Signals")
    FAmmoValueChange AmmoValueChange;
			
    void FireStart();
    void FireStop();
    void Reload();
    void ChangeFireMode();

  protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ALMABaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    UAnimMontage *ReloadMontage;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void SpawnWeapon();

	bool bIsShooting = false;
	bool AnimReloading = false;

	WeaponFireMode FireMode;

	float WeaponFireRate;    
	void WeaponFire();
	void WeaponReload();
    void InitAnimNotify();
	void OnNotifyReloadFinished(USkeletalMeshComponent *SkeletalMesh);
	bool CantReload() const;

	UFUNCTION()
	void OnBulletsValueChange(int NewBullets, int MaxBull) { AmmoValueChange.Broadcast(NewBullets, MaxBull);}

	FTimerHandle FireTimer;
};
