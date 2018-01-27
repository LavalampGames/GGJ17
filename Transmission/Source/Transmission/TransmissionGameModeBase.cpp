// Fill out your copyright notice in the Description page of Project Settings.

#include "TransmissionGameModeBase.h"

void ATransmissionGameModeBase::SequenceBegin(ASequence* sequence, AStimulus* stimulus, int channel)
{
	sequence_channels_[channel] = sequence;
	sequence->SequenceBegin(stimulus);
}

void ATransmissionGameModeBase::SequenceResponse(AResponse* response, ESequenceChannel channels)
{
	switch (channels)
	{
	case ESequenceChannel::VE_One:
	{
		if (sequence_channels_[0] != nullptr)
			sequence_channels_[0]->SequenceResolve(response);
		break;
	}
	case ESequenceChannel::VE_Two:
	{
		if (sequence_channels_[1] != nullptr)
			sequence_channels_[1]->SequenceResolve(response);
		break;
	}
	case ESequenceChannel::VE_Three:
	{
		if (sequence_channels_[2] != nullptr)
			sequence_channels_[2]->SequenceResolve(response);
		break;
	}
	case ESequenceChannel::VE_All:
	{
		for (int i = 0; i < 3; i++)
			if (sequence_channels_[i] != nullptr)
				sequence_channels_[i]->SequenceResolve(response);
		break;
	}
	}
}


