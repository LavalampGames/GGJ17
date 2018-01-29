// Fill out your copyright notice in the Description page of Project Settings.

#include "GameGroup.h"
#include "TransmissionGameModeBase.h"
#include "Engine/World.h"

// Sets default values
AGameGroup::AGameGroup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	in_event_ = false;
	is_robot_ = false;

	group_speed_ = 5;
}

// Called when the game starts or when spawned
void AGameGroup::BeginPlay()
{
	Super::BeginPlay();
	
	// randomly select a location in the world to go to
	ATransmissionGameModeBase* game_mode = (ATransmissionGameModeBase*)GetWorld()->GetAuthGameMode();
	TArray<AGameLocation*> locations = game_mode->game_world_->GetLocations();
	target_location_ = locations[FMath::RandRange(0, locations.Num() - 1)];

	// randomise starting location
	FVector2D start;
	start.X = FMath::RandRange(0, 99);
	start.Y = FMath::RandRange(0, 99);
	SetPosition(start);
}

// Called every frame
void AGameGroup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (in_event_ == false)
	{
		time_since_last_event_ += DeltaTime;
	}
}

TArray<AGameCharacter*> AGameGroup::GetCharacters()
{
	return characters_;
}

void AGameGroup::EndOfDay()
{
	for (AGameCharacter* character : characters_)
	{
		character->food_level_ -= 0.25f;
	}

	if (has_eaten_ == false)
		GroupEat();

	if (has_healed_ == false)
		GroupHeal();

	TArray<AGameCharacter*> characters = GetCharacters();
	for (AGameCharacter* character : characters)
	{
		if (character->food_level_ <= 0)
		{
			character->TakeCharacterDamage(-0.25 + character->food_level_);
		}
	}

	has_eaten_ = false;
	has_healed_ = false;
	has_fought_ = false;

	GroupMove();
}

void AGameGroup::GroupMove()
{
	// move towards the location
	if (target_location_ != nullptr)
	{
		FVector2D target_position = target_location_->GetPosition();
		if (target_position.X > current_location_.X)
		{
			current_location_.X = (FMath::Abs(current_location_.X - target_position.X) >= group_speed_) ? current_location_.X + group_speed_ : current_location_.X + FMath::Abs(current_location_.X - target_position.X);
		}
		else if (target_position.X < current_location_.X)
		{
			current_location_.X = (FMath::Abs(current_location_.X - target_position.X) >= group_speed_) ? current_location_.X - group_speed_ : current_location_.X - FMath::Abs(current_location_.X - target_position.X);
		}

		if (target_position.Y > current_location_.Y)
		{
			current_location_.Y = (FMath::Abs(current_location_.Y - target_position.Y) >= group_speed_) ? current_location_.Y + group_speed_ : current_location_.Y + FMath::Abs(current_location_.Y - target_position.Y);
		}
		else if (target_position.Y < current_location_.Y)
		{
			current_location_.Y = (FMath::Abs(current_location_.Y - target_position.Y) >= group_speed_) ? current_location_.Y - group_speed_ : current_location_.Y - FMath::Abs(current_location_.Y - target_position.Y);
		}

		ATransmissionGameModeBase* game_mode = (ATransmissionGameModeBase*)GetWorld()->GetAuthGameMode();
		TArray<AGameLocation*> locations = game_mode->game_world_->GetLocations();
		if (target_position == current_location_)
		{
			FString alert = "A group of " + FString::FromInt(characters_.Num()) + " people recently passed through.";
			target_location_->AddAlert(alert);

			// take supplies from the location
			food_supply_level_ += target_location_->ModifyFoodSupplies(characters_.Num() * 3);
			medical_supply_level_ += target_location_->ModifyMedicalSupplies(characters_.Num());
			combat_supply_level_ += target_location_->ModifyCombatSupplies(characters_.Num());

			// randomly select a location in the world to go to
			AGameLocation* prev_location = target_location_;
			while (target_location_ == prev_location)
			{
				
				target_location_ = locations[FMath::RandRange(0, locations.Num() - 1)];
			}
		}
		else
		{
			if (is_robot_ == false)
			{
				// check if the group has passed close to any other locations
				for (AGameLocation* location : locations)
				{
					if (location != target_location_)
					{
						if (FVector2D::Distance(current_location_, location->GetPosition()) <= 5)
						{
							FString alert = "A group of " + FString::FromInt(characters_.Num()) + " people recently passed nearby.";
							location->AddAlert(alert);
						}
					}
				}
			}
			else
			{
				// find the nearest location
				AGameLocation* nearest = nullptr;
				float nearest_distance = 0;
				for (AGameLocation* location : locations)
				{
					if (nearest == nullptr || nearest_distance > FVector2D::Distance(current_location_, location->GetPosition()))
					{
						nearest = location;
						nearest_distance = FVector2D::Distance(current_location_, location->GetPosition());
					}
				}

				// send an alert message
				FString alert = "Robot spotted nearby.";
				nearest->AddAlert(alert);
			}
		}
	}
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
	return time_since_last_event_  / 2.0f;
}

void AGameGroup::GroupEat()
{
	if (food_supply_level_ >= characters_.Num() * FOOD_SUPPLY_COST)
	{
		for (AGameCharacter* character : characters_)
		{
			character->food_level_ += 0.25f;
			if (character->food_level_ > 1.0f)
				character->food_level_ = 1.0f;
			food_supply_level_ -= FOOD_SUPPLY_COST;
		}

		has_eaten_ = true;
	}
}

void AGameGroup::GroupHeal()
{
	int injury_count = 0;
	for (AGameCharacter* character : characters_)
	{
		if (character->health_level_ < 0.5f)
			injury_count++;
	}

	if (medical_supply_level_ >= injury_count * MEDICAL_SUPPLY_COST)
	{
		for (AGameCharacter* character : characters_)
		{
			character->health_level_ += 0.25f;
			if (character->health_level_ > 1.0f)
				character->health_level_ = 1.0f;
		}
		medical_supply_level_ -= injury_count * MEDICAL_SUPPLY_COST;
	}
}

void AGameGroup::AddCharacter(AGameCharacter* character)
{
	characters_.Add(character);
	character->SetParentGroup(this);
}

void AGameGroup::RemoveCharacter(AGameCharacter* character)
{
	characters_.Remove(character);
	character->Destroy();
}
