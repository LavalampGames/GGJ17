// Fill out your copyright notice in the Description page of Project Settings.

#include "GenericEvent.h"
#include "Engine/World.h"
#include "TransmissionGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GenericConversationSequence.h"
#include "Responder.h"

AGenericEvent::AGenericEvent()
{
	event_lines_.Add(LOCTEXT("", "Hello?"));
	event_lines_.Add(LOCTEXT("", "Is anyone out there?"));
}
void AGenericEvent::BeginEvent_Implementation()
{
	if (associated_groups_.Num() <= 0)
		return;

	associated_groups_[0]->SetIsInEvent(true);

	AGenericConversationSequence* sequence = GetWorld()->SpawnActor<AGenericConversationSequence>();
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

void AGenericEvent::ProgressEvent_Implementation()
{
	associated_groups_[0]->SetIsInEvent(false);
	associated_groups_[0]->SetTimeSinceLastEvent(0);

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


