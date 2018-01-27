// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameCharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameGroup.generated.h"

USTRUCT()
struct FCharacterAndInfluence
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	AGameCharacter* character;

	UPROPERTY(BlueprintReadWrite)
	float influence_level;
};

UCLASS()
class TRANSMISSION_API AGameGroup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameGroup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Getter for group characters
	TArray<FCharacterAndInfluence> GetCharacters();

	// Getter for combat supply level
	UFUNCTION(BlueprintCallable, Category = "Group Management")
	inline float GetCombatSupplyLevel() { return combat_supply_level_; }

	// Getter for medical supply level
	UFUNCTION(BlueprintCallable, Category = "Group Management")
	inline float GetMedicalSupplyLevel() { return medical_supply_level_; }

	// Getter for food level
	UFUNCTION(BlueprintCallable, Category = "Group Management")
	inline float GetFoodSupplyLevel() { return food_supply_level_; }

	// Data modifier for combat supply level
	UFUNCTION(BlueprintCallable, Category = "Group Management")
	float ModifyCombatSupplyLevel(float amount);

	// Data modifier for medical supply level
	UFUNCTION(BlueprintCallable, Category = "Group Management")
	float ModifyMedicalSupplyLevel(float amount);

	// Data modifier for food supply level
	UFUNCTION(BlueprintCallable, Category = "Group Management")
	float ModifyFoodSupplyLevel(float amount);

	// Getter for group story events
	UFUNCTION(BlueprintCallable, Category = "Event Management")
	inline TArray<AGameEvent*> GetStoryEvents() { return story_events_; }

	// Calculate the multiplier for food generic event
	UFUNCTION(BlueprintCallable, Category = "Event Managment")
	float CalculateFoodEventMultiplier();

	// Calculate the multiplier for medical generic event
	UFUNCTION(BlueprintCallable, Category = "Event Managment")
	float CalculateMedicalEventMultiplier();
	
	// Calculate the multiplier for generic event
	UFUNCTION(BlueprintCallable, Category = "Event Managment")
	float CalculateGenericEventMultiplier();

protected:

	/**
	* Custom story events attached to this specific group
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Event Management")
	TArray<AGameEvent*> story_events_;

	/**
	* Container for characters in the group and their influence over group decisions
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Character Management")
	TArray<FCharacterAndInfluence> characters_;

	/**
	* Tracker for food supply level of group
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Group Management")
	float food_supply_level_;

	/**
	* Tracker for medical supply level of group
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Group Management")
	float medical_supply_level_;

	/**
	* Tracker for combat supply level of group
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Group Management")
	float combat_supply_level_;

	/**
	* Tracker for current world location of group
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Group Management")
	FVector2D current_location_;

	/**
	* Tracker for duration since last event
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Group Management")
	float time_since_last_event_;

	/**
	* Tracker for if group is engaged in event
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Group Management")
	bool in_event_;

	/**
	* Tracker for if group has consumed food yet this day
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Group Management")
	bool has_eaten_;
};
