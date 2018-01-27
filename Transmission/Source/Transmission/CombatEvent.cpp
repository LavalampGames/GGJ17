// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatEvent.h"
#include "Engine/World.h"
#include "TransmissionGameModeBase.h"

void ACombatEvent::BeginEvent_Implementation()
{
	ATransmissionGameModeBase* game_mode = (ATransmissionGameModeBase*)GetWorld()->GetAuthGameMode();
	game_mode->SimulateCombatEvent(combat_groups_[0], combat_groups_[1]);
}

void ACombatEvent::ProgressEvent_Implementation()
{
}

void ACombatEvent::BackgroundResolveEvent_Implementation()
{
}

float ACombatEvent::CalculateEventMultiplier_Implementation()
{
	return 0.0f;
}


