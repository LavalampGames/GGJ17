// Fill out your copyright notice in the Description page of Project Settings.

#include "GameGroup.h"

// Sets default values
AGameGroup::AGameGroup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	in_event_ = false;
}

// Called when the game starts or when spawned
void AGameGroup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameGroup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (in_event_ == false)
		time_since_last_event_ += DeltaTime;
}

TArray<AGameCharacter*> AGameGroup::GetCharacters()
{
	return characters_;
}

float AGameGroup::ModifyCombatSupplyLevel(float amount)
{
	if (amount < 0)
	{
		if (combat_supply_level_ >= amount)
		{
			combat_supply_level_ -= amount;
			return amount;
		}
		else
		{
			float return_value = combat_supply_level_;
			combat_supply_level_ = 0;
			return return_value;
		}
	}
	else
	{
		combat_supply_level_ += amount;
		return 0;
	}
}

float AGameGroup::ModifyMedicalSupplyLevel(float amount)
{
	if (amount < 0)
	{
		if (medical_supply_level_ >= amount)
		{
			medical_supply_level_ -= amount;
			return amount;
		}
		else
		{
			float return_value = medical_supply_level_;
			medical_supply_level_ = 0;
			return return_value;
		}
	}
	else
	{
		medical_supply_level_ += amount;
		return 0;
	}
}

float AGameGroup::ModifyFoodSupplyLevel(float amount)
{
	if (amount < 0)
	{
		if (food_supply_level_ >= amount)
		{
			food_supply_level_ -= amount;
			return amount;
		}
		else
		{
			float return_value = food_supply_level_;
			food_supply_level_ = 0;
			return return_value;
		}
	}
	else
	{
		food_supply_level_ += amount;
		return 0;
	}
}

float AGameGroup::CalculateFoodEventMultiplier()
{
	if (has_eaten_)
		return 0.0f;

	float required_food = FOOD_SUPPLY_COST * characters_.Num();
	if (required_food < food_supply_level_)
	{
		return (required_food - food_supply_level_) * time_since_last_event_;
	}

	return 0.0f;
}

float AGameGroup::CalculateMedicalEventMultiplier()
{
	if (has_healed_)
		return 0.0f;

	float required_medicine = FOOD_SUPPLY_COST * characters_.Num();
	if (required_medicine < medical_supply_level_)
	{
		return (required_medicine - medical_supply_level_) * time_since_last_event_;
	}

	return 0.0f;
}

float AGameGroup::CalculateGenericEventMultiplier()
{
	return time_since_last_event_ * 2.0f;
}

void AGameGroup::GroupEat()
{
	if (food_supply_level_ >= characters_.Num() * FOOD_SUPPLY_COST)
	{
		for (AGameCharacter* character : characters_)
		{
			character->food_level_ += 0.25f;
			food_supply_level_ -= FOOD_SUPPLY_COST;
		}
	}
}

void AGameGroup::GroupHeal()
{
}
