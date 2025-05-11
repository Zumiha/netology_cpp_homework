// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMADefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ULMAHealthComponent;

struct FInputActionValue;


UCLASS()
class LEAVEMEALONE_API ALMADefaultCharacter : public ACharacter {
  GENERATED_BODY()

public:
  ALMADefaultCharacter();

protected:
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  USpringArmComponent *SpringArmComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UCameraComponent *CameraComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Health")
  ULMAHealthComponent *HealthComponent;





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

  virtual void BeginPlay() override;

  void RotationPlayerOnCursor();

  void Look(const FInputActionValue &Value);

public:
  virtual void Tick(float DeltaTime) override;

  virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponentx	) override;

private:
  float YRotation = -75.0f;

  float ArmLength = 1400.0f;

  float FOV = 55.0f;

  void MoveForward(float Value);
  void MoveRight(float Value);

  void CameraZoom(float Value);
};
