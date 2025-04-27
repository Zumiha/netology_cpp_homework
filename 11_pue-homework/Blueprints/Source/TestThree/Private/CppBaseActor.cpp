// Fill out your copyright notice in the Description page of Project Settings.


#include "CppBaseActor.h"
#include "Engine/Engine.h"
#include <Kismet/GameplayStatics.h>
#include "Math/UnrealMathUtility.h"

// Sets default values
ACppBaseActor::ACppBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void ACppBaseActor::BeginPlay()
{
	Super::BeginPlay();
	++ACppBaseActor::InstanceID;
    InitLocation = GetActorLocation();
}

// Called every frame
void ACppBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACppBaseActor::ShowActorInformation()
{
	UE_LOG(LogTemp, Display, TEXT("Instance Name: %s_%d"), *PlayerName, ACppBaseActor::InstanceID);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, PlayerName, true, FVector2D(2.0f, 2.0f));
	UE_LOG(LogTemp, Display, TEXT("EnemyNum: %d"), this->EnemyNum);
	UE_LOG(LogTemp, Display, TEXT("IsAlive: %i"), this->IsAlive);
}

void ACppBaseActor::SinMovement() {
	FVector ActorNewLocation = this->InitLocation;
	ActorNewLocation.Z = this->Amplitude * FMath::Sin(this->Frequency * UGameplayStatics::GetRealTimeSeconds((GetWorld()))) + this->InitLocation.Z;
	SetActorLocation(ActorNewLocation, false, nullptr, ETeleportType::None);
}

