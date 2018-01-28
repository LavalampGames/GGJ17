// Fill out your copyright notice in the Description page of Project Settings.

#include "FoodEvent.h"
#include "Engine/World.h"
#include "FoodConversationSequence.h"
#include "TransmissionGameModeBase.h"

void AFoodEvent::BeginEvent_Implementation()
{
	if (associated_groups_.Num() <= 0)
		return;

	AFoodConversationSequence* sequence = GetWorld()->SpawnActor<AFoodConversationSequence>();
	event_sequences_.Add(sequence);

	ATransmissionGameModeBase* game_mode = (ATransmissionGameModeBase*)GetWorld()->GetAuthGameMode();
	AStimulus* stimulus = GetWorld()->SpawnActor<AStimulus>();
	stimulus->groups_.Add(associated_groups_[0]);

	game_mode->SequenceBegin(sequence, stimulus, 0);
}

void AFoodEvent::ProgressEvent_Implementation()
{
	associated_groups_[0]->SetIsInEvent(false);

	// clean up the sequence
	event_sequences_[0]->Destroy();
	this->Destroy();
}

void AFoodEvent::BackgroundResolveEvent_Implementation()
{
}

float AFoodEvent::CalculateEventMultiplier_Implementation()
{
	return 0.0f;
}


