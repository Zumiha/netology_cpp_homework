// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CppBaseActor.generated.h"

//class UStaticMeshComponent;

UENUM(BlueprintType)
enum class EMovementsState : uint8 {
	Mobility,
	Static
};

USTRUCT(BlueprintType)
struct FTransformStruct {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector CurrentLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator CurrentRotation = FRotator::ZeroRotator;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector CurrentScale = FVector(1.0f, 1.0f, 1.0f);
};


UCLASS()
class TESTTHREE_API ACppBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACppBaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	static inline int InstanceID{};

	UPROPERTY(VisibleAnywhere)
	FString PlayerName = this->GetClass()->GetName();
	
	UPROPERTY(EditAnywhere)
	int EnemyNum = 0;

	UPROPERTY(EditDefaultsOnly)
	float CurrentHealth = 99.999;

	UPROPERTY(EditInstanceOnly)
	bool IsAlive = true;

	UPROPERTY(EditAnywhere)
	float Amplitude = 100.0;

    UPROPERTY(EditAnywhere)
    float Frequency = 1.5707;

    UPROPERTY(EditAnywhere)
    FVector InitLocation;


	UFUNCTION(BlueprintCallable)
	void ShowActorInformation();

	UFUNCTION(BlueprintCallable)
	void SinMovement();

      public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;


private:

};
