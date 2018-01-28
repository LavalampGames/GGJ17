// Fill out your copyright notice in the Description page of Project Settings.

#include "GenericEvent.h"
#include "Engine/World.h"
#include "TransmissionGameModeBase.h"
#include "GenericConversationSequence.h"

void AGenericEvent::BeginEvent_Implementation()
{
	AGenericConversationSequence* sequence = GetWorld()->SpawnActor<AGenericConversationSequence>();
	event_sequences_.Add(sequence);

	ATransmissionGameModeBase* game_mode = (ATransmissionGameModeBase*)GetWorld()->GetAuthGameMode();
	AStimulus* stimulus = GetWorld()->SpawnActor<AStimulus>();
	stimulus->groups_.Add(associated_groups_[0]);

	game_mode->SequenceBegin(sequence, nullptr, 0);
}

void AGenericEvent::ProgressEvent_Implementation()
{
	associated_groups_[0]->SetIsInEvent(false);

	// clean up the sequence
	event_sequences_[0]->Destroy();
	this->Destroy();
}

void AGenericEvent::BackgroundResolveEvent_Implementation()
{
}

float AGenericEvent::CalculateEventMultiplier_Implementation()
{
	return 0.0f;
}


