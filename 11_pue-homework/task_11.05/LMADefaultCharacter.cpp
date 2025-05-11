// Fill out your copyright notice in the Description page of Project Settings.


#include "LMADefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/InputComponent.h"

#include "../Components/LMAHealthComponent.h"

#include "GameFramework/SpringArmComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "InputActionValue.h"
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
  
  HealthComponent = CreateDefaultSubobject<ULMAHealthComponent>("HealthComponent");
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
}



void ALMADefaultCharacter::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);
    RotationPlayerOnCursor();
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

void ALMADefaultCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ALMADefaultCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ALMADefaultCharacter::MoveRight);
    PlayerInputComponent->BindAxis("CameraZoom", this, &ALMADefaultCharacter::CameraZoom);

}

void ALMADefaultCharacter::Look(const FInputActionValue &Value) {
  // input is a Vector2D
  FVector2D LookAxisVector = Value.Get<FVector2D>();

  if (Controller != nullptr) {
    // add yaw and pitch input to controller
    AddControllerYawInput(LookAxisVector.X);
    AddControllerPitchInput(LookAxisVector.Y);
  }
}

void ALMADefaultCharacter::MoveForward(float Value) {
    AddMovementInput(GetActorForwardVector(), Value);
}

void ALMADefaultCharacter::MoveRight(float Value) {
    AddMovementInput(GetActorRightVector(), Value);
}

void ALMADefaultCharacter::CameraZoom(float Value) {
   if (Value == 0.0f || Controller == nullptr)
     return;

   ArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength + Value * ZoomStep, MinZoomLenght, MaxZoomLenght);
   SpringArmComponent->TargetArmLength = FMath::FInterpTo(SpringArmComponent->TargetArmLength, ArmLength, GetWorld()->GetDeltaSeconds(), 100.f );
      
}
