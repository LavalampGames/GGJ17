// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameEvent.h"
#include "GameCharacter.generated.h"

const float MEDICAL_SUPPLY_COST = 1.0f;
const float FOOD_SUPPLY_COST = 1.0f;

UCLASS()
class TRANSMISSION_API AGameCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Calculate the characters current combat level
	UFUNCTION(BlueprintCallable, Category = "Attribute Management")
	float CalculateCombatLevel();

	// Apply damage to the character
	UFUNCTION(BlueprintCallable, Category = "Attribute Management")
	void TakeCharacterDamage(float damage);

public:
	/**
	* Character's name used to identify them in events
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Attribute")
	FString character_name_;

	/**
	* Personality modifier representing how much this character trusts the player
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Attribute")
	float trust_level_;
	
	/**
	* Custom story events attached to this specific character
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Attribute")
	TArray<AGameEvent*> story_events_;

	/**
	* Personality modifier representing how violently this character reacts to others
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Attribute")
	float aggression_level_;

	/**
	* Personality modifer representing this characters combat proficiency
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Attribute")
	float combat_level_;

	/**
	* Personality modifier representing this characters medical proficiency
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Attribute")
	float medical_level_;

	/**
	* Personality modifier representing this characters survival proficiency
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Attribute")
	float survival_level_;

	/**
	* Personality modifier representing this characters age
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Attribute")
	float age_;

	/**
	* Modifier for this characters general health level
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Attribute")
	float health_level_;

	/**
	* Modifier for this characters food level
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Attribute")
	float food_level_;
};
