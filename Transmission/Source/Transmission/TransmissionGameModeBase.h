// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sequence.h"
#include "CoreMinimal.h"
#include "Response.h"
#include "GameGroup.h"
#include "GameFramework/GameModeBase.h"
#include "GameWorld.h"
#include "TransmissionGameModeBase.generated.h"

UENUM(BlueprintType)
enum class ESequenceChannel: uint8
{
	VE_One 	UMETA(DisplayName = "One"),
	VE_Two 	UMETA(DisplayName = "Two"),
	VE_Three	UMETA(DisplayName = "Three"),
	VE_All	UMETA(DisplayName = "All")
};

UCLASS()
class TRANSMISSION_API ATransmissionGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Sequence Management")
	void SequenceBegin(ASequence* sequence, AStimulus* stimulus, int channel);

	UFUNCTION(BlueprintCallable, Category = "Sequence Management")
	void SequenceResponse(AResponse* response, ESequenceChannel channels);

	// Simulator for combat event between two groups
	UFUNCTION(BlueprintCallable, Category = "Game Management")
	void SimulateCombatEvent(AGameGroup* groupA, AGameGroup* groupB);

public:
	AGameWorld* game_world_;

protected:
	// sequence channels
	ASequence* sequence_channels_[3];
};
