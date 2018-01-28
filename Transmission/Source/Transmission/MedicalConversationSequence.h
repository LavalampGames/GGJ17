// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sequence.h"
#include "MedicalConversationSequence.generated.h"

/**
 * 
 */
UCLASS()
class TRANSMISSION_API AMedicalConversationSequence : public ASequence
{
	GENERATED_BODY()
	
public:

	virtual void SequenceBegin(AStimulus* stimulus) override;
	virtual void SequenceResolve(AResponse* response) override;
	virtual void SequenceResolveNoResponse() override;

protected:

	void JuryRig();
	void Triage();
	void Leave();
	
	
};
