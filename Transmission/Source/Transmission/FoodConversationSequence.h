// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sequence.h"
#include "FoodConversationSequence.generated.h"

/**
 * 
 */
UCLASS()
class TRANSMISSION_API AFoodConversationSequence : public ASequence
{
	GENERATED_BODY()
	
public:
	
	virtual void SequenceBegin(AStimulus* stimulus) override;
	virtual void SequenceResolve(AResponse* response) override;
	virtual void SequenceResolveNoResponse() override;
	
	
};
