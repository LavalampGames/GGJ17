// Fill out your copyright notice in the Description page of Project Settings.

#include "GameWorld.h"
#include "Engine/World.h"
#include "GenericEvent.h"
#include "MedicalEvent.h"
#include "CombatEvent.h"
#include "FoodEvent.h"
#include <algorithm>

// Sets default values
AGameWorld::AGameWorld()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	day_number_ = 53;
	day_timer_ = 0;
	day_length_ = 120.0f;
	first_move_ = false;
	attracting_robots_ = false;

	player_location_ = "Kentville";
	minimum_required_event_ = day_length_ / 6.0f;
}

// Called when the game starts or when spawned
void AGameWorld::BeginPlay()
{
	Super::BeginPlay();
	
	// create three groups of survivors
	for (int i = 0; i < 5; i++)
	{
		AGameGroup* group = GetWorld()->SpawnActor<AGameGroup>();
		
		// create a random number of survivors
		int survivor_count = FMath::RandRange(5, 10);
		for (int j = 0; j < survivor_count; j++)
		{
			AGameCharacter* character = GetWorld()->SpawnActor<AGameCharacter>();
			group->AddCharacter(character);
		}
		group->ModifyFoodSupplyLevel(survivor_count * 3.0f);
		group->ModifyMedicalSupplyLevel(survivor_count);
		group->ModifyCombatSupplyLevel((survivor_count / 2) + 1);

		player_controlled_groups_.Add(group);
	}

	// create some robots
	for (int i = 0; i < 5; i++)
	{
		SpawnRobots(1);
	}

	for (int i = 0; i < player_controlled_groups_.Num(); i++)
	{
		player_controlled_groups_[i]->group_index_ = i;
	}
}

float AGameWorld::CalculateCombatEventMultiplier(AGameGroup * group, AGameGroup*& targetGroup)
{
	if (group->GetHasFought())
		return 0.0f;

	// check if any player groups are nearby
	FVector2D current_location = group->GetPosition();
	float nearest_distance = 1000;
	AGameGroup* target_group = nullptr;
	for (AGameGroup* enemy_group : player_controlled_groups_)
	{
		if (enemy_group != group && enemy_group->GetIsInEvent() == false && enemy_group->GetHasFought() == false && (!group->is_robot_ || !enemy_group->is_robot_))
		{
			FVector2D target_location = enemy_group->GetPosition();

			float distance = FVector2D::Distance(current_location, target_location);
			if (distance < nearest_distance)
			{
				nearest_distance = distance;
				target_group = enemy_group;
			}
		}
	}

	targetGroup = target_group;

	if (target_group != nullptr)
	{
		if (nearest_distance > 10.0f)
			return group->GetTimeSinceLastEvent() * 1.5f;
		else
			return group->GetTimeSinceLastEvent() * 2.0f;
	}
	else
	{
		return 0.0f;
	}
}

void AGameWorld::TransitionDay()
{
	day_timer_ = 0;
	day_number_++;

	for (AGameLocation* location : locations_)
	{
		location->ClearLocationAlerts();
	}

	TArray<AGameGroup*> dead_groups;
	for (AGameGroup* group : player_controlled_groups_)
	{
		group->EndOfDay();
		if (group->GetCharacters().Num() <= 0)
			dead_groups.Add(group);
	}
	
	for (AGameGroup* d_group : dead_groups)
	{
		// find the nearest location
		AGameLocation* nearest = nullptr;
		float nearest_distance = 0;
		for (AGameLocation* location : locations_)
		{
			if (nearest == nullptr || nearest_distance > FVector2D::Distance(d_group->GetPosition(), location->GetPosition()))
			{
				nearest = location;
				nearest_distance = FVector2D::Distance(d_group->GetPosition(), location->GetPosition());
			}
		}

		// send an alert message
		FString alert = "Human remains found nearby.";
		nearest->AddAlert(alert);

		player_controlled_groups_.Remove(d_group);
		d_group->Destroy();
	}
	dead_groups.Empty();

	for (AGameGroup* group : autonomous_groups_)
	{
		group->GroupMove();		
		if (group->GetCharacters().Num() <= 0)
			dead_groups.Add(group);
	}

	for (AGameGroup* d_group : dead_groups)
	{
		// find the nearest location
		AGameLocation* nearest = nullptr;
		float nearest_distance = 0;
		for (AGameLocation* location : locations_)
		{
			if (nearest == nullptr || nearest_distance > FVector2D::Distance(d_group->GetPosition(), location->GetPosition()))
			{
				nearest = location;
				nearest_distance = FVector2D::Distance(d_group->GetPosition(), location->GetPosition());
			}
		}

		// send an alert message
		FString alert = "Robot destroyed nearby.";
		nearest->AddAlert(alert);

		autonomous_groups_.Remove(d_group);
		d_group->Destroy();
	}
	dead_groups.Empty();
}

void AGameWorld::SpawnRobots(int count)
{
	AGameGroup* robot_group = GetWorld()->SpawnActor<AGameGroup>();

	for (int i = 0; i < count; i++)
	{
		AGameCharacter* robot = GetWorld()->SpawnActor<AGameCharacter>();
		robot->combat_level_ = 9001;
		robot->medical_level_ = 0;
		robot->survival_level_ = 0;
		robot_group->AddCharacter(robot);
	}

	FVector2D pos;
	pos.X = FMath::RandRange(0, 99);
	pos.Y = FMath::RandRange(0, 99);
	robot_group->SetPosition(pos);
	robot_group->is_robot_ = true;
	autonomous_groups_.Add(robot_group);
}

void AGameWorld::ToggleRobotAttract()
{
	if (attracting_robots_)
	{
		// set robot target locations to random
		for (AGameGroup* group : autonomous_groups_)
		{
			int location_index = FMath::RandRange(0, locations_.Num() - 1);
			group->SetTargetLocation(locations_[location_index]);
		}

		attracting_robots_ = false;
	}
	else
	{
		AGameLocation* location = GetLocationByName(player_location_);
		for (AGameGroup* group : autonomous_groups_)
		{
			group->SetTargetLocation(location);
		}
	}
}

AGameLocation * AGameWorld::GetLocationByName(FString location_name)
{
	for (AGameLocation* location : locations_)
	{

	}
	return nullptr;
}

AGameLocation * AGameWorld::GetNearestLocation(FVector2D position)
{
	AGameLocation* closest_location = nullptr;
	float closest_distance = 10000;
	for (AGameLocation* location : locations_)
	{
		float distance = FVector2D::Distance(location->GetPosition(), position);
		if (closest_location == nullptr || distance < closest_distance)
		{
			closest_location = location;
			closest_distance = distance;
		}
	}

	return closest_location;
}

int AGameWorld::GetRemainingHumans()
{
	int count = 0;
	for (AGameGroup* group : player_controlled_groups_)
	{
		count += group->GetCharacters().Num();
	}

	return count;
}

// Called every frame
void AGameWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	day_timer_ += DeltaTime;
	if (day_timer_ >= day_length_)
	{
		TransitionDay();
		first_move_ = false;
	}
	else if (day_timer_ >= day_length_ / 2.0f && first_move_ == false)
	{
		for (AGameGroup* group : player_controlled_groups_)
			group->GroupMove();

		for (AGameGroup* group : autonomous_groups_)
			group->GroupMove();

		first_move_ = true;
	}

	// loop through the player controlled groups
	for (AGameGroup* group : player_controlled_groups_)
	{
		if (group->GetIsInEvent() == false)
		{
			AGameEvent* current_event = nullptr;
			float highest_multiplier = 0;

			// first check if there are any active group story events
			for (AGameEvent* story_event : group->GetStoryEvents())
			{
				float multiplier = story_event->CalculateEventMultiplier();
				if (multiplier > 0)
				{
					current_event = story_event;
					highest_multiplier = multiplier;
					break;
				}
			}

			// if a story event has been found then execute it immediatly
			if (current_event != nullptr)
			{
				group->SetIsInEvent(true);
				current_event->BeginEvent();
				continue;
			}

			// check if there are any active character story events - but don't yet because I can't be arsed

			// check the 4 generic events
			AGameGroup* targetGroup = nullptr;
			float food_event_multiplier = group->CalculateFoodEventMultiplier();
			float medical_event_multiplier = group->CalculateMedicalEventMultiplier();
			float generic_event_multiplier = group->CalculateGenericEventMultiplier();
			float combat_event_multiplier = CalculateCombatEventMultiplier(group, targetGroup);

			// determine the highest multiplier
			highest_multiplier = std::max(food_event_multiplier, std::max(medical_event_multiplier, std::max(generic_event_multiplier, combat_event_multiplier)));

			TArray<AGameEvent*> auto_resolve_events;
			if (food_event_multiplier >= minimum_required_event_)
			{
				// spawn the food event
				AFoodEvent* food_event = GetWorld()->SpawnActor<AFoodEvent>();
				food_event->associated_groups_.Add(group);
				if (food_event_multiplier == highest_multiplier)
					current_event = food_event;
				else
					auto_resolve_events.Add(food_event);
			}

			if (medical_event_multiplier >= minimum_required_event_)
			{
				// spawn the food event
				AMedicalEvent* medical_event = GetWorld()->SpawnActor<AMedicalEvent>();
				medical_event->associated_groups_.Add(group);
				if (medical_event_multiplier == highest_multiplier)
					current_event = medical_event;
				else
					auto_resolve_events.Add(medical_event);
			}

			if (combat_event_multiplier >= minimum_required_event_)
			{
				// spawn the combat event
				ACombatEvent* combat_event = GetWorld()->SpawnActor<ACombatEvent>();
				combat_event->associated_groups_.Add(group);
				combat_event->associated_groups_.Add(targetGroup);
				if (combat_event_multiplier == highest_multiplier)
					current_event = combat_event;
				else
					auto_resolve_events.Add(combat_event);
			}

			if (generic_event_multiplier >= minimum_required_event_ && generic_event_multiplier == highest_multiplier)
			{
				// spawn the generic event
				AGenericEvent* generic_event = GetWorld()->SpawnActor<AGenericEvent>();
				generic_event->associated_groups_.Add(group);
				current_event = generic_event;
			}

			// first resolve the player controlled event
			if (current_event != nullptr)
			{
				group->SetIsInEvent(true);
				current_event->BeginEvent();
			}

			// next resolve any background events
			for (AGameEvent* hidden_event : auto_resolve_events)
			{
				hidden_event->BackgroundResolveEvent();
			}

			auto_resolve_events.Empty();
		}
	}

	// clean up dead groups
	TArray<AGameGroup*> dead_groups;
	for (AGameGroup* group : player_controlled_groups_)
	{
		if (group->GetCharacters().Num() <= 0)
			dead_groups.Add(group);
	}

	for (AGameGroup* d_group : dead_groups)
	{
		player_controlled_groups_.Remove(d_group);
		d_group->Destroy();
	}
	dead_groups.Empty();

	for (AGameGroup* group : autonomous_groups_)
	{
		if (group->GetCharacters().Num() <= 0)
			dead_groups.Add(group);
	}

	for (AGameGroup* d_group : dead_groups)
	{
		// send alerts
		autonomous_groups_.Remove(d_group);
		d_group->Destroy();
	}
	dead_groups.Empty();
}
