// Fill out your copyright notice in the Description page of Project Settings.

#include "GenericEvent.h"
#include "Engine/World.h"
#include "TransmissionGameModeBase.h"

void AGenericEvent::BeginEvent_Implementation()
{

}

void AGenericEvent::ProgressEvent_Implementation()
{
	associated_group_->SetIsInEvent(false);

	// clean up the sequence
}

void AGenericEvent::BackgroundResolveEvent_Implementation()
{
}

float AGenericEvent::CalculateEventMultiplier_Implementation()
{
	return 0.0f;
}


