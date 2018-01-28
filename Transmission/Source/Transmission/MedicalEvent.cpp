// Fill out your copyright notice in the Description page of Project Settings.

#include "MedicalEvent.h"
#include "GameGroup.h"
#include "TransmissionGameModeBase.h"
#include "MedicalConversationSequence.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "responder.h"

void AMedicalEvent::BeginEvent_Implementation()
{
	if (associated_groups_.Num() <= 0)
		return;

	associated_groups_[0]->SetIsInEvent(true);

	AMedicalConversationSequence* sequence = GetWorld()->SpawnActor<AMedicalConversationSequence>();
	sequence->SetParentEvent(this);
	event_sequences_.Add(sequence);

	ATransmissionGameModeBase* game_mode = (ATransmissionGameModeBase*)GetWorld()->GetAuthGameMode();
	AStimulus* stimulus = GetWorld()->SpawnActor<AStimulus>();
	stimulus->groups_.Add(associated_groups_[0]);

	TArray<AActor*> responders;
	UGameplayStatics::GetAllActorsOfClass(this, AResponder::StaticClass(), responders);
	AResponder* responder = (AResponder*)(responders[0]);

	int response_index = FMath::RandRange(0, event_lines_.Num() - 1);
	//responder->DisplayResponseText(event_lines_[response_index]);

	game_mode->SequenceBegin(sequence, stimulus, 0);
}

void AMedicalEvent::ProgressEvent_Implementation()
{
}

void AMedicalEvent::BackgroundResolveEvent_Implementation()
{
}

float AMedicalEvent::CalculateEventMultiplier_Implementation()
{

	return 0.0f;
}
