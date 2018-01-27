// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameGroup.h"
#include "GameEvent.h"
#include "GameWorld.generated.h"

USTRUCT()
struct FEventAndMultiplier
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	AGameEvent* character;

	UPROPERTY(BlueprintReadWrite)
	float total_multiplier;
};

UCLASS()
class TRANSMISSION_API AGameWorld : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameWorld();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to calculate the combat chance of a group
	float CalculateCombatEventMultiplier(AGameGroup* group);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	/**
	* Player controlled groups that are currently active in the world
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Group Management")
	TArray<AGameGroup*> player_controlled_groups_;

	/**
	* Autonomous groups that are currently active in the world
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Group Management")
	TArray<AGameGroup*> autonomous_groups_;

	float minimum_required_event_;
};
