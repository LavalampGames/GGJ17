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

	day_number_ = 1;
	day_timer_ = 0;

	minimum_required_event_ = DAY_LENGTH / 3.0f;
}

// Called when the game starts or when spawned
void AGameWorld::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < player_controlled_groups_.Num(); i++)
	{
		player_controlled_groups_[i]->group_index_ = i;
	}
}

float AGameWorld::CalculateCombatEventMultiplier(AGameGroup * group)
{
	return 0.0f;
}

void AGameWorld::TransitionDay()
{
	day_timer_ = 0;
	day_number_++;
}

// Called every frame
void AGameWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	day_timer_ += DeltaTime;
	if (day_timer_ >= DAY_LENGTH)
	{
		TransitionDay();
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
			float food_event_multiplier = group->CalculateFoodEventMultiplier();
			float medical_event_multiplier = group->CalculateMedicalEventMultiplier();
			float generic_event_multiplier = group->CalculateGenericEventMultiplier();
			float combat_event_multiplier = CalculateCombatEventMultiplier(group);

			// determine the highest multiplier
			highest_multiplier = std::max(food_event_multiplier, std::max(medical_event_multiplier, std::max(generic_event_multiplier, combat_event_multiplier)));

			TArray<AGameEvent*> auto_resolve_events;
			if (food_event_multiplier >= minimum_required_event_)
			{
				// spawn the food event
				AGameEvent* food_event = nullptr;
				if (food_event_multiplier == highest_multiplier)
					current_event = food_event;
				else
					auto_resolve_events.Add(food_event);
			}

			if (medical_event_multiplier >= minimum_required_event_)
			{
				// spawn the food event
				AGameEvent* medical_event = nullptr;
				if (medical_event_multiplier == highest_multiplier)
					current_event = medical_event;
				else
					auto_resolve_events.Add(medical_event);
			}

			if (combat_event_multiplier >= minimum_required_event_)
			{
				// spawn the combat event
				ACombatEvent* combat_event = GetWorld()->SpawnActor<ACombatEvent>();
				if (combat_event_multiplier == highest_multiplier)
					current_event = combat_event;
				else
					auto_resolve_events.Add(combat_event);
			}

			if (generic_event_multiplier >= minimum_required_event_ && generic_event_multiplier == highest_multiplier)
			{
				// spawn the generic event
				AGenericEvent* generic_event = GetWorld()->SpawnActor<AGenericEvent>();
				generic_event->SetGroup(group);
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
		}
	}
}
