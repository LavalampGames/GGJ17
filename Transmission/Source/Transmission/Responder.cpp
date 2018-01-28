// Fill out your copyright notice in the Description page of Project Settings.

#include "Responder.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AResponder::AResponder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	responder_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Responder Visuals"));
	responder_mesh_->SetupAttachment(RootComponent);

	responder_audio_ = CreateDefaultSubobject<UAudioComponent>(TEXT("Responder Audio"));
	responder_audio_->SetupAttachment(responder_mesh_);

	response_offset_location_ = CreateDefaultSubobject<USceneComponent>(TEXT("Offset Location"));
	response_offset_location_->SetupAttachment(responder_mesh_);

	OnClicked.AddDynamic(this, &AResponder::ClickResponse);

	response_channel_ = 0;
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

void AResponder::DisplayAvailableResponses()
{
	FVector offset = response_offset_location_->GetComponentTransform().GetLocation();
	int index = 0;
	for (AResponse* response : available_responses_)
	{
		response->SetActorLocation(offset);
		response->response_text_renderer_->SetVisibility(true);
		response->response_text_renderer_->SetText(response->response_text_);
		offset.Z += 25;
	}
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

void AResponder::ClickResponse(AActor* other, FKey key)
{
	responder_audio_->Play();

	DisplayAvailableResponses();
}
