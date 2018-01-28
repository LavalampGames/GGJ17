// Fill out your copyright notice in the Description page of Project Settings.

#include "FoodConversationSequence.h"
#include "Engine/World.h"
#include "Responder.h"

void AFoodConversationSequence::SequenceBegin(AStimulus* stimulus)
{
	expiry_time_ = 4.0f;

	stimulus_ = stimulus;
}

void AFoodConversationSequence::SequenceResolve(AResponse * response)
{
}

void AFoodConversationSequence::SequenceResolveNoResponse()
{
	int decision = FMath::RandRange(0, 3);

	switch (decision)
	{
	case 0:
	{
		Hunt();
		break;
	}
	case 1:
	{
		FeedYoung();
		break;
	}
	case 2:
	{
		FeedStrong();
		break;
	}
	case 3:
	{
		FeedWeak();
		break;
	}
	}

	stimulus_->groups_[0]->SetIsInEvent(false);
	CleanupResponses();
}

void AFoodConversationSequence::Hunt()
{
	AGameGroup* group = stimulus_->groups_[0];

	float survival_count = 0;
	for (AGameCharacter* character : group->GetCharacters())
	{
		survival_count = character->survival_level_;
	}

	int character_count = group->GetCharacters().Num();
	survival_count -= FMath::RandRange(0, character_count);

	if (survival_count > character_count / 2)
	{
		group->ModifyFoodSupplyLevel(character_count);
	}
	else if (survival_count < character_count / 4)
	{
		int character_index = FMath::RandRange(0, character_count - 1);
		group->GetCharacters()[character_index]->TakeCharacterDamage(0.5f);
	}
}

void AFoodConversationSequence::FeedYoung()
{
	AGameGroup* group = stimulus_->groups_[0];

	TArray<AGameCharacter*> characters = group->GetCharacters();
	while (group->GetFoodSupplyLevel() > 0)
	{
		AGameCharacter* lowest = nullptr;
		for (AGameCharacter* character : characters)
		{
			if (lowest == nullptr || lowest->age_ > character->age_)
			{
				lowest = character;
			}
		}

		lowest->food_level_ += 0.25f;
		group->ModifyFoodSupplyLevel(FOOD_SUPPLY_COST);
		characters.Remove(lowest);
	}

	group->SetHasEaten(true);
}

void AFoodConversationSequence::FeedStrong()
{
	AGameGroup* group = stimulus_->groups_[0];

	TArray<AGameCharacter*> characters = group->GetCharacters();
	while (group->GetFoodSupplyLevel() > 0)
	{
		AGameCharacter* highest = nullptr;
		for (AGameCharacter* character : characters)
		{
			if (highest == nullptr || highest->health_level_ > character->combat_level_)
			{
				highest = character;
			}
		}

		highest->food_level_ += 0.25f;
		group->ModifyFoodSupplyLevel(FOOD_SUPPLY_COST);
		characters.Remove(highest);
	}

	group->SetHasEaten(true);
}

void AFoodConversationSequence::FeedWeak()
{
	AGameGroup* group = stimulus_->groups_[0];

	TArray<AGameCharacter*> characters = group->GetCharacters();
	while (group->GetFoodSupplyLevel() > 0)
	{
		AGameCharacter* lowest = nullptr;
		for (AGameCharacter* character : characters)
		{
			if (lowest == nullptr || lowest->health_level_ > character->health_level_)
			{
				lowest = character;
			}
		}

		lowest->food_level_ += 0.25f;
		group->ModifyFoodSupplyLevel(FOOD_SUPPLY_COST);
		characters.Remove(lowest);
	}

	group->SetHasEaten(true);
}
