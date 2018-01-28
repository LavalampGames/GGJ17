// Fill out your copyright notice in the Description page of Project Settings.

#include "GameLocation.h"


// Sets default values
AGameLocation::AGameLocation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameLocation::BeginPlay()
{
	Super::BeginPlay();
	
	food_supply_level_ = FMath::RandRange(1, 10);
	medical_supply_level_ = FMath::RandRange(1, 10);
	combat_supply_level_ = FMath::RandRange(1, 10);
}

// Called every frame
void AGameLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// calculate the likelihood of a supply drop
	if (drop_timer_ <= 0.0f)
	{
		int drop_chance = 0;
		if (food_supply_level_ <= 0.0f)
			drop_chance++;

		if (medical_supply_level_ <= 0.0f)
			drop_chance++;

		if (combat_supply_level_ <= 0.0f)
			drop_chance++;

		if (drop_chance > 0)
		{
			drop_chance = FMath::RandRange(drop_chance, 6);

			if (drop_chance == 6)
			{
				// spawn a supply drop and add an alert
				drop_timer_ = 360.0f;
				food_supply_level_ += FMath::RandRange(1, 5);
				medical_supply_level_ += FMath::RandRange(1, 5);
				combat_supply_level_ += FMath::RandRange(1, 5);

				FString alert = "A government supply drop has been dropped at this location.";
				AddAlert(alert);
			}
		}
	}
	else
	{
		drop_timer_ -= DeltaTime;
	}
}

void AGameLocation::AddAlert(FString alert)
{
	if (current_alerts_.Num() >= 3)
	{
		FString del_alert = current_alerts_[0];
		current_alerts_.Remove(del_alert);
	}
	current_alerts_.Add(alert);
}

int AGameLocation::ModifyFoodSupplies(int amount)
{
	if (amount > food_supply_level_)
	{
		int level = food_supply_level_;
		food_supply_level_ = 0;
		return level;
	}
	else
	{
		food_supply_level_ -= amount;
		return amount;
	}
}

int AGameLocation::ModifyMedicalSupplies(int amount)
{
	if (amount > medical_supply_level_)
	{
		int level = medical_supply_level_;
		medical_supply_level_ = 0;
		return level;
	}
	else
	{
		medical_supply_level_ -= amount;
		return amount;
	}
}

int AGameLocation::ModifyCombatSupplies(int amount)
{
	if (amount > combat_supply_level_)
	{
		int level = combat_supply_level_;
		combat_supply_level_ = 0;
		return level;
	}
	else
	{
		combat_supply_level_ -= amount;
		return amount;
	}
}

