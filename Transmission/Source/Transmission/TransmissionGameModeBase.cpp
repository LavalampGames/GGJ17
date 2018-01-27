// Fill out your copyright notice in the Description page of Project Settings.

#include "TransmissionGameModeBase.h"
#include "Misc/OutputDevice.h"
#include <sstream>

void ATransmissionGameModeBase::SequenceBegin(ASequence* sequence, AStimulus* stimulus, int channel)
{
	sequence_channels_[channel] = sequence;
	const void* pointer = static_cast<const void*>(stimulus);
	std::stringstream ss;
	ss << pointer;
	//FString address = TEXT(ss.str());
	//FOutputDeviceDebug debug;
	//CallFunctionByNameWithArguments(TEXT("Sequence Begin 0"), debug, this, true);
	sequence->SequenceBegin(stimulus);
}

void ATransmissionGameModeBase::SequenceResponse(AResponse* response, ESequenceChannel channels)
{
	switch (channels)
	{
	case ESequenceChannel::VE_One:
	{
		if (sequence_channels_[0] != nullptr)
			sequence_channels_[0]->SequenceResolve(response);
		break;
	}
	case ESequenceChannel::VE_Two:
	{
		if (sequence_channels_[1] != nullptr)
			sequence_channels_[1]->SequenceResolve(response);
		break;
	}
	case ESequenceChannel::VE_Three:
	{
		if (sequence_channels_[2] != nullptr)
			sequence_channels_[2]->SequenceResolve(response);
		break;
	}
	case ESequenceChannel::VE_All:
	{
		for (int i = 0; i < 3; i++)
			if (sequence_channels_[i] != nullptr)
				sequence_channels_[i]->SequenceResolve(response);
		break;
	}
	}
}

void ATransmissionGameModeBase::SimulateCombatEvent(AGameGroup* groupA, AGameGroup* groupB)
{
	// calculate group A combat score
	TArray<AGameCharacter*> group_A_characters = groupA->GetCharacters();
	float group_a_combat_total = 0;
	for (int i = 0; i < group_A_characters.Num(); i++)
	{
		group_a_combat_total += group_A_characters[i]->CalculateCombatLevel();
	}
	group_a_combat_total *= (groupA->GetCombatSupplyLevel() <= group_A_characters.Num()) ? groupA->GetCombatSupplyLevel() / group_A_characters.Num() : 1.0f;
	
	// apply a multiplier to the attacker's score
	group_a_combat_total *= 1.1f;

	// calculate group B combat score
	TArray<AGameCharacter*> group_B_characters = groupB->GetCharacters();
	float group_b_combat_total = 0;
	for (int i = 0; i < group_B_characters.Num(); i++)
	{
		group_b_combat_total += group_B_characters[i]->CalculateCombatLevel();
	}
	group_b_combat_total *= (groupB->GetCombatSupplyLevel() <= group_B_characters.Num()) ? groupB->GetCombatSupplyLevel() / group_B_characters.Num() : 1.0f;

	// calculate and apply the results of combat
	if (group_b_combat_total > group_a_combat_total)
	{
		for (int i = 0; i < group_A_characters.Num(); i++)
		{
			group_A_characters[i]->TakeCharacterDamage(0.5f);
		}
		// victor steals supplies from loser
		groupB->ModifyCombatSupplyLevel(groupA->ModifyCombatSupplyLevel(1.0f));
		groupB->ModifyMedicalSupplyLevel(groupA->ModifyMedicalSupplyLevel(1.0f));
		groupB->ModifyFoodSupplyLevel(groupA->ModifyFoodSupplyLevel(4.0f));
	}
	else
	{
		for (int i = 0; i < group_B_characters.Num(); i++)
		{
			group_B_characters[i]->TakeCharacterDamage(0.5f);
		}
		// victor steals supplies from loser
		groupA->ModifyCombatSupplyLevel(groupB->ModifyCombatSupplyLevel(1.0f));
		groupA->ModifyMedicalSupplyLevel(groupB->ModifyMedicalSupplyLevel(1.0f));
		groupA->ModifyFoodSupplyLevel(groupB->ModifyFoodSupplyLevel(4.0f));
	}
}