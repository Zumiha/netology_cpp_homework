// Fill out your copyright notice in the Description page of Project Settings.


#include "LMADefaultCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/InputComponent.h"

#include "LeaveMeAlone/Components/Health/LMAHealthComponent.h"
#include "LeaveMeAlone/Components/Weapon/LMAWeaponComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "Engine/Engine.h"

ALMADefaultCharacter::ALMADefaultCharacter() {

  PrimaryActorTick.bCanEverTick = true;

  SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
  SpringArmComponent->SetupAttachment(GetRootComponent());
  SpringArmComponent->SetUsingAbsoluteRotation(true);
  SpringArmComponent->TargetArmLength = ArmLength;
  SpringArmComponent->SetRelativeRotation(FRotator(YRotation, 0.0f, 0.0f));
  SpringArmComponent->bDoCollisionTest = false;
  SpringArmComponent->bEnableCameraLag = true;

  CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
  CameraComponent->SetupAttachment(SpringArmComponent);
  CameraComponent->SetFieldOfView(FOV);
  CameraComponent->bUsePawnControlRotation = false;

  bUseControllerRotationPitch = false;
  bUseControllerRotationYaw = false;
  bUseControllerRotationRoll = false;

  GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
  GetCharacterMovement()->MaxCustomMovementSpeed = SprintSpeed;
   
  HealthComponent = CreateDefaultSubobject<ULMAHealthComponent>("HealthComponent");
  WeaponComponent = CreateDefaultSubobject<ULMAWeaponComponent>("WeaponComponent");

}

void ALMADefaultCharacter::BeginPlay() {
  Super::BeginPlay();

    if (CursorMaterial) {
        CurrentCursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), CursorMaterial, CursorSize, FVector(0));
    }
    if (ArmLength < MinZoomLenght) {
      ArmLength = MinZoomLenght;
    } else if (ArmLength > MaxZoomLenght) {
      ArmLength = MaxZoomLenght;
    } 
    SpringArmComponent->TargetArmLength = ArmLength;

	//OnHealthChanged(HealthComponent->GetHealth());
	//HealthComponent->OnDeath.AddUObject(this, &ALMADefaultCharacter::OnDeath);
     
	HealthComponent->OnDeath.AddDynamic(this, &ALMADefaultCharacter::OnDeath);
    //HealthComponent->OnHealthChanged.AddDynamic(this, &ALMADefaultCharacter::OnHealthChanged);
}



void ALMADefaultCharacter::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
	if (!(HealthComponent->IsDead()))
	{
		RotationPlayerOnCursor();
	}

    if (IsSprinting) {
        StaminaCurrent = StaminaCurrent - StaminaDrain * GetWorld()->GetDeltaSeconds();
      if (StaminaCurrent <= 0) {
        SprintEnd();
        StaminaCurrent = 0;
        InStaminaRecovery = true;
      }
    } else if (StaminaCurrent < StaminaMaximum) {
        StaminaCurrent = StaminaCurrent + StaminaRecovery * GetWorld()->GetDeltaSeconds();
        InStaminaRecovery = StaminaCurrent > 15 ? false : true;
        if (StaminaCurrent > StaminaMaximum) StaminaCurrent = StaminaMaximum;
    }

}

void ALMADefaultCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ALMADefaultCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ALMADefaultCharacter::MoveRight);
    PlayerInputComponent->BindAxis("CameraZoom", this, &ALMADefaultCharacter::CameraZoom);

    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ALMADefaultCharacter::SprintStart);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ALMADefaultCharacter::SprintEnd);

    PlayerInputComponent->BindAction("FireMode", IE_Pressed, WeaponComponent, &ULMAWeaponComponent::ChangeFireMode);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &ULMAWeaponComponent::FireStart);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &ULMAWeaponComponent::FireStop);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &ULMAWeaponComponent::Reload);    
}

void ALMADefaultCharacter::MoveForward(float Value) {
    AddMovementInput(GetActorForwardVector(), Value);
}

void ALMADefaultCharacter::MoveRight(float Value) {
    AddMovementInput(GetActorRightVector(), Value);
}

void ALMADefaultCharacter::SprintStart() { 
    if (InStaminaRecovery) return;
    IsSprinting = true; 
    GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}
void ALMADefaultCharacter::SprintEnd() { 
    IsSprinting = false;
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ALMADefaultCharacter::CameraZoom(float Value) {
   if (Value == 0.0f || Controller == nullptr)
     return;

   ArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + Value * ZoomStep, MinZoomLenght, MaxZoomLenght);
   SpringArmComponent->TargetArmLength = FMath::FInterpTo(SpringArmComponent->TargetArmLength, ArmLength, GetWorld()->GetDeltaSeconds(), 100.f );   
}

void ALMADefaultCharacter::RotationPlayerOnCursor() {
  APlayerController *PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
  if (PC) {
    FHitResult ResultHit;
    
    PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, ResultHit);
    auto FindRotatorResult = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ResultHit.Location);
    SetActorRotation(FQuat(FRotator(0.0f, FindRotatorResult.Yaw, FindRotatorResult.Roll)));


     if (CurrentCursor) {
         CurrentCursor->SetWorldLocation(ResultHit.Location);
     }
  }
}

void ALMADefaultCharacter::OnDeath() {
  //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("PLAYER DEATH")), true, FVector2D(7.f, 7.f));
  //CurrentCursor->DestroyRenderState_Concurrent();

  PlayAnimMontage(DeathMontage);

  GetCharacterMovement()->DisableMovement();

  SetLifeSpan(5.0f);

  if (Controller) {
    Controller->ChangeState(NAME_Spectating);
  }
}

void ALMADefaultCharacter::OnHealthChanged(float NewHealth) {
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Health = %f"), NewHealth));
}