// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatEvent.h"
#include "Engine/World.h"
#include "TransmissionGameModeBase.h"

void ACombatEvent::BeginEvent_Implementation()
{
	if (associated_groups_.Num() <= 0)
		return;

	ATransmissionGameModeBase* game_mode = (ATransmissionGameModeBase*)GetWorld()->GetAuthGameMode();

	associated_groups_[0]->SetIsInEvent(true);
	associated_groups_[1]->SetIsInEvent(true);

	game_mode->SimulateCombatEvent(associated_groups_[0], associated_groups_[1]);

	ProgressEvent_Implementation();
}

void ACombatEvent::ProgressEvent_Implementation()
{
	associated_groups_[0]->SetIsInEvent(false);
	associated_groups_[0]->SetTimeSinceLastEvent(0);
	associated_groups_[0]->SetHasFought(true);

	associated_groups_[1]->SetIsInEvent(false);
	associated_groups_[1]->SetTimeSinceLastEvent(0);
	associated_groups_[1]->SetHasFought(true);

	ATransmissionGameModeBase* game_mode = (ATransmissionGameModeBase*)GetWorld()->GetAuthGameMode();
	AGameLocation* location = game_mode->game_world_->GetNearestLocation(associated_groups_[0]->GetPosition());

	FString alert = "Fighting has been heard nearby.";
	location->AddAlert(alert);

	this->Destroy();
}

void ACombatEvent::BackgroundResolveEvent_Implementation()
{
}

float ACombatEvent::CalculateEventMultiplier_Implementation()
{
	return 0.0f;
}


