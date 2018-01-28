// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameGroup.h"
#include "CoreMinimal.h"
#include "GameEvent.h"
#include "CombatEvent.generated.h"

/**
 * 
 */
UCLASS()
class TRANSMISSION_API ACombatEvent : public AGameEvent
{
	GENERATED_BODY()

public:

	virtual void BeginEvent_Implementation() override;
	virtual void ProgressEvent_Implementation() override;
	virtual void BackgroundResolveEvent_Implementation() override;
	virtual float CalculateEventMultiplier_Implementation() override;
	
protected:
};
