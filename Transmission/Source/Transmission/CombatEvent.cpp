// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatEvent.h"
#include "Engine/World.h"
#include "TransmissionGameModeBase.h"

void ACombatEvent::BeginEvent_Implementation()
{
	ATransmissionGameModeBase* game_mode = (ATransmissionGameModeBase*)GetWorld()->GetAuthGameMode();

	associated_groups_[0]->SetIsInEvent(true);
	associated_groups_[1]->SetIsInEvent(true);

	game_mode->SimulateCombatEvent(associated_groups_[0], associated_groups_[1]);
}

void ACombatEvent::ProgressEvent_Implementation()
{
	associated_groups_[0]->SetIsInEvent(false);
	associated_groups_[0]->SetTimeSinceLastEvent(0);

	associated_groups_[1]->SetIsInEvent(false);
	associated_groups_[1]->SetTimeSinceLastEvent(0);

	this->Destroy();
}

void ACombatEvent::BackgroundResolveEvent_Implementation()
{
}

float ACombatEvent::CalculateEventMultiplier_Implementation()
{
	return 0.0f;
}


