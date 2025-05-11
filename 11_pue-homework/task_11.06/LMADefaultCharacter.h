// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMADefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ULMAHealthComponent;

class UAnimMontage;

UCLASS()
class LEAVEMEALONE_API ALMADefaultCharacter : public ACharacter {
  GENERATED_BODY()

public:
  ALMADefaultCharacter();

  UFUNCTION()
  ULMAHealthComponent *GetHealthComponent() const { return HealthComponent; }

  UFUNCTION()
  bool GetSprinting() const { return IsSprinting; }

protected:
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Health")
  ULMAHealthComponent* HealthComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  USpringArmComponent *SpringArmComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UCameraComponent *CameraComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement|Speed")
  float WalkSpeed = 500.f;
  
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement|Speed")
  float SprintSpeed = 900.f;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement|Speed")
  bool IsSprinting = false;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement|Speed")
  bool InStaminaRecovery = false;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement|Stamina")
  float StaminaMaximum = 100.f;
    
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement|Stamina")
  float StaminaCurrent = 100.f;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement|Stamina")
  float StaminaDrain = 20.f;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement|Stamina")
  float StaminaRecovery = 10.f;


  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Zoom")
  float MinZoomLenght = 10.0f;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Zoom")
  float MaxZoomLenght = 2000.0f;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Zoom")
  float ZoomStep = 20.f;

  UPROPERTY()
  UDecalComponent *CurrentCursor = nullptr;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
  UMaterialInterface *CursorMaterial = nullptr;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
  FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);

  UPROPERTY(EditDefaultsOnly, Category = "Animation")
  UAnimMontage *DeathMontage;

  virtual void BeginPlay() override;

public:
  virtual void Tick(float DeltaTime) override;

  virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponentx	) override;

private:
  float YRotation = -75.0f;

  float ArmLength = 1400.0f;

  float FOV = 55.0f;

  void MoveForward(float Value);
  void MoveRight(float Value);
  void SprintStart();
  void SprintEnd();


  void CameraZoom(float Value);
  void RotationPlayerOnCursor();

  void OnDeath();
  void OnHealthChanged(float NewHealth);
};
