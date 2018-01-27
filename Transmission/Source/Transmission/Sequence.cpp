// Fill out your copyright notice in the Description page of Project Settings.

#include "Sequence.h"


// Sets default values
ASequence::ASequence()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASequence::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASequence::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// track the duration the sequence has existed for and execute a 'no response' logic if the time expires
	response_wait_timer_ += DeltaTime;
	if (response_wait_timer_ >= expiry_time_)
	{
		SequenceResolveNoResponse();
	}
}

void ASequence::CleanupResponses()
{
	for (int i = 0; i < responses_.Num(); i++)
	{
		AResponder* responder = responses_[i]->GetParentResponder();
		responses_[i]->Destroy();
	}
	responses_.Empty();
}

