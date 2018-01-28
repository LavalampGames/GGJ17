// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameGroup.h"
#include "GameEvent.h"
#include "GameLocation.h"
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
	float CalculateCombatEventMultiplier(AGameGroup* group, AGameGroup*& targetGroup);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// transisitions the day
	void TransitionDay();

	// returns the locations in the game
	UFUNCTION(BlueprintCallable, Category = "World Management")
	TArray<AGameLocation*> GetLocations() { return locations_; }

	// spawns a group of robots of count size in the world
	UFUNCTION(BlueprintCallable, Category = "World Management")
	void SpawnRobots(int count);

	// attracts robots to your location
	UFUNCTION(BlueprintCallable, Category = "World Management")
	void ToggleRobotAttract();
	
	// get location by name
	UFUNCTION(BlueprintCallable, Category = "World Management")
	AGameLocation* GetLocationByName(FString location_name);

	UFUNCTION(BlueprintCallable, Category = "World Management")
	float GetDayTimer() { return day_timer_; }

	UFUNCTION(BlueprintCallable, Category = "World Management")
	int GetDayNumber() { return day_number_; }

	UFUNCTION(BlueprintCallable, Category = "World Management")
	float GetDayLength() { return day_length_; }

	UFUNCTION(BlueprintCallable, Category = "World Management")
	AGameLocation* GetNearestLocation(FVector2D position);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "World Management")
	int GetRemainingHumans();

public:
	// Location of the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Management")
	FString player_location_;

protected:
	/**
	* Length of a single day
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Management")
	float day_length_;

	/**
	* Locations within the game world
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Management")
	TArray<AGameLocation*> locations_;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Management")
	float day_timer_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Management")
	int day_number_;

	bool first_move_;

	bool attracting_robots_;
};
