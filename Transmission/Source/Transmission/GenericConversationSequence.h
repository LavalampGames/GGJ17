// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sequence.h"
#include "GenericConversationSequence.generated.h"

/**
 * 
 */
UCLASS()
class TRANSMISSION_API AGenericConversationSequence : public ASequence
{
	GENERATED_BODY()
	
public:
	virtual void SequenceBegin(AStimulus* stimulus) override;
	virtual void SequenceResolve(AResponse* response) override;
	virtual void SequenceResolveNoResponse() override;

protected:
	void Hunt();
	void Scavenge();
	void Redirect();
	void Nothing();
};
