// LeaveMeAlone Game by Netology. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMAEnemyCharacter.generated.h"

class ULMAHealthComponent;
class UBehaviorTree;

UCLASS()
class LEAVEMEALONE_API ALMAEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALMAEnemyCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree *BehaviorTreeAsset;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Health")
    ULMAHealthComponent *HealthComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement|Speed")
	float WalkSpeed = 300.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement|Speed")
    float SprintSpeed = 600.f;

  public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
