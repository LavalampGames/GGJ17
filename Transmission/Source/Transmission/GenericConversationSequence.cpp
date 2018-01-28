// Fill out your copyright notice in the Description page of Project Settings.

#include "GenericConversationSequence.h"
#include "Responder.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Stimulus.h"
#include "TransmissionGameModeBase.h"

void AGenericConversationSequence::SequenceBegin(AStimulus* stimulus)
{
	expiry_time_ = 4.0f;

	stimulus_ = stimulus;

}

void AGenericConversationSequence::SequenceResolve(AResponse * response)
{
	CleanupResponses();
}

void AGenericConversationSequence::SequenceResolveNoResponse()
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
		Scavenge();
		break;
	}
	case 2:
	{
		Redirect();
		break;
	}
	case 3:
	{
		Nothing();
		break;
	}
	}

	stimulus_->groups_[0]->SetIsInEvent(false);
	CleanupResponses();
}

void AGenericConversationSequence::Hunt()
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

void AGenericConversationSequence::Scavenge()
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
		group->ModifyMedicalSupplyLevel(character_count / 2);
		group->ModifyCombatSupplyLevel(character_count / 4);
	}
	else if (survival_count < character_count / 4)
	{
		int character_index = FMath::RandRange(0, character_count - 1);
		group->GetCharacters()[character_index]->TakeCharacterDamage(0.5f);
	}
}

void AGenericConversationSequence::Redirect()
{
	ATransmissionGameModeBase* game_mode = (ATransmissionGameModeBase*)GetWorld()->GetAuthGameMode();
	AGameWorld* game_world = game_mode->game_world_;

	int location_count = FMath::RandRange(0, game_world->GetLocations().Num() - 1);

	AGameGroup* group = stimulus_->groups_[0];
	group->SetTargetLocation(game_world->GetLocations()[location_count]);

}

void AGenericConversationSequence::Nothing()
{
}


