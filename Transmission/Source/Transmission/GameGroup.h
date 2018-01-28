// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameCharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameGroup.generated.h"

USTRUCT(BlueprintType)
struct FCharacterAndInfluence
{
	GENERATED_BODY()

	FCharacterAndInfluence()
	{
		character = nullptr;
		influence_level = 0;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Group")
	AGameCharacter* character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Group")
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
	TArray<AGameCharacter*> GetCharacters();

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

	// Getter for is in event
	UFUNCTION(BlueprintCallable, Category = "Event Managment")
	inline bool GetIsInEvent() { return in_event_; }

	// Setter for is in event
	UFUNCTION(BlueprintCallable, Category = "Event Managment")
	void SetIsInEvent(bool value) { in_event_ = value; }

	// Logic for group eating
	UFUNCTION(BlueprintCallable, Category = "Group Management")
	void GroupEat();

	// setter for has eaten
	UFUNCTION(BlueprintCallable, Category = "Group Management")
	void SetHasEaten(bool eaten) { has_eaten_ = eaten; }

	// Logic for group eating
	UFUNCTION(BlueprintCallable, Category = "Group Management")
	void GroupHeal();

	// setter for group direction
	UFUNCTION(BlueprintCallable, Category = "Group Management")
	void SetTargetLocation(AGameLocation* location) { target_location_ = location; }

	// add a character to the group
	UFUNCTION(BlueprintCallable, Category = "Group Management")
	void AddCharacter(AGameCharacter* character);
	
	// remove a character from the group
	UFUNCTION(BlueprintCallable, Category = "Group Management")
	void RemoveCharacter(AGameCharacter* character);

	// setter for group position
	UFUNCTION(BlueprintCallable, Category = "Group Management")
	void SetPosition(FVector2D position) { current_location_ = position; }
	
	UFUNCTION(BlueprintCallable, Category = "Group Management")
	FVector2D GetPosition() { return current_location_; }

	UFUNCTION(BlueprintCallable, Category = "Group Management")
	float GetTimeSinceLastEvent() { return time_since_last_event_; }

	UFUNCTION(BlueprintCallable, Category = "Group Management")
	void SetTimeSinceLastEvent(float time) { time_since_last_event_ = time; }

	// processing for end of day
	UFUNCTION(BlueprintCallable, Category = "Group Management")
	void EndOfDay();

	UFUNCTION(BlueprintCallable, Category = "Group Management")
	void GroupMove();

public:
	int group_index_;

protected:
	/**
	* Current target location of the group
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Management")
	AGameLocation* target_location_;

	/**
	* Custom story events attached to this specific group
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Management")
	TArray<AGameEvent*> story_events_;

	/**
	* Container for characters in the group and their influence over group decisions
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Management")
	TArray<AGameCharacter*> characters_;

	/**
	* Tracker for food supply level of group
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Group Management")
	float food_supply_level_;

	/**
	* Tracker for medical supply level of group
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Group Management")
	float medical_supply_level_;

	/**
	* Tracker for combat supply level of group
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Group Management")
	float combat_supply_level_;

	/**
	* Tracker for current world location of group
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Group Management")
	FVector2D current_location_;

	/**
	* Tracker for duration since last event
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Group Management")
	float time_since_last_event_;

	/**
	* Tracker for if group is engaged in event
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Group Management")
	bool in_event_;

	/**
	* Tracker for if group has consumed food yet this day
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Group Management")
	bool has_eaten_;

	/**
	* Tracker for if group has healed yet this day
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Group Management")
	bool has_healed_;

	/**
	* Group speed
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Group Management")
	float group_speed_;
};
