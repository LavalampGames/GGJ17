// Fill out your copyright notice in the Description page of Project Settings.

#include "GameCharacter.h"


// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	character_name_ = "Joeneric";
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Determine combat level from health and base level
float AGameCharacter::CalculateCombatLevel()
{
	float combat_level = (health_level_ < 0.25f) ? combat_level_ * 0.5f : combat_level_;
	combat_level *= aggression_level_;
	return combat_level;
}

void AGameCharacter::TakeCharacterDamage(float amount)
{

}