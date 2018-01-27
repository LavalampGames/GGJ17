// Fill out your copyright notice in the Description page of Project Settings.

#include "Responder.h"


// Sets default values
AResponder::AResponder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AResponder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResponder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Add single response to this object
void AResponder::AddResponse(AResponse* response)
{
	available_responses_.Add(response);
	response->SetParentResponder(this);
}

// Add responses to this object
void AResponder::AddResponses(TArray<AResponse*> responses)
{
	for (int i = 0; i < responses.Num(); i++)
	{
		available_responses_.Add(responses[i]);
		responses[i]->SetParentResponder(this);
	}
}

// Remove a response from this object
void AResponder::RemoveResponse(AResponse* response)
{
	available_responses_.Remove(response);
}
