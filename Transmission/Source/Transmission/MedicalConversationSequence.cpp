// Fill out your copyright notice in the Description page of Project Settings.

#include "MedicalConversationSequence.h"


void AMedicalConversationSequence::SequenceBegin(AStimulus* stimulus)
{
	expiry_time_ = 2.0f;

	stimulus_ = stimulus;
}

void AMedicalConversationSequence::SequenceResolve(AResponse * response)
{
}

void AMedicalConversationSequence::SequenceResolveNoResponse()
{
	int decision = FMath::RandRange(0, 2);

	switch (decision)
	{
	case 0:
	{
		JuryRig();
		break;
	}
	case 1:
	{
		Triage();
		break;
	}
	case 2:
	{
		Leave();
		break;
	}
	}

	stimulus_->groups_[0]->SetIsInEvent(false);
	CleanupResponses();
}

void AMedicalConversationSequence::JuryRig()
{
	AGameGroup* group = stimulus_->groups_[0];

	float medicince_average = 0;
	for (AGameCharacter* character : group->GetCharacters())
	{
		medicince_average += character->medical_level_;
	}
	medicince_average /= group->GetCharacters().Num();

	// heal heavily injured characters
	TArray<AGameCharacter*> remaining_characters = group->GetCharacters();
	for (AGameCharacter* character : group->GetCharacters())
	{
		if (character->health_level_ < 0.5f)
		{
			bool healed = (medicince_average >= (1.0f - character->health_level_) * 2);
			if (healed)
				character->health_level_ += 0.25f;
			else
				character->TakeCharacterDamage(0.25f);

			remaining_characters.Remove(character);
		}
	}

	// heal the remaining characters
	for (AGameCharacter* character : remaining_characters)
	{
		character->health_level_ += 0.25f;
		if (character->health_level_ > 1.0f)
			character->health_level_ = 1.0f;
	}

	group->SetHasHealed(true);
}

void AMedicalConversationSequence::Triage()
{
	AGameGroup* group = stimulus_->groups_[0];

	TArray<AGameCharacter*> characters = group->GetCharacters();
	while (group->GetMedicalSupplyLevel() > 0)
	{
		AGameCharacter* lowest = nullptr;
		for (AGameCharacter* character : characters)
		{
			if (lowest == nullptr || lowest->health_level_ > character->health_level_)
			{
				lowest = character;
			}
		}

		lowest->health_level_ += 0.25f;
		group->ModifyMedicalSupplyLevel(-MEDICAL_SUPPLY_COST);
		characters.Remove(lowest);
	}

	// heal the remforaining characters
	for (AGameCharacter* character : characters)
	{
		if (character->health_level_ > 0.5f)
		{
			character->health_level_ += 0.25f;
			if (character->health_level_ > 1.0f)
				character->health_level_ = 1.0f;
		}
	}

	group->SetHasHealed(true);
}

void AMedicalConversationSequence::Leave()
{
	AGameGroup* group = stimulus_->groups_[0];

	int injury_count = 0;
	for (AGameCharacter* character : group->GetCharacters())
	{
		if (character->health_level_ < 0.5f)
			injury_count++;
	}

	TArray<AGameCharacter*> characters = group->GetCharacters();
	while (group->GetMedicalSupplyLevel() < injury_count * MEDICAL_SUPPLY_COST)
	{
		AGameCharacter* lowest = nullptr;
		for (AGameCharacter* character : characters)
		{
			if (lowest == nullptr || lowest->health_level_ > character->health_level_)
			{
				lowest = character;
			}
		}

		group->RemoveCharacter(lowest);

		injury_count = 0;
		for (AGameCharacter* character : group->GetCharacters())
		{
			if (character->health_level_ < 0.5f)
				injury_count++;
		}
	}

	// heal the remforaining characters
	for (AGameCharacter* character : characters)
	{
		if (character->health_level_ < 0.5f)
			group->ModifyMedicalSupplyLevel(-MEDICAL_SUPPLY_COST);

		character->health_level_ += 0.25f;
		if (character->health_level_ > 1.0f)
			character->health_level_ = 1.0f;
		
	}

	group->SetHasHealed(true);
}