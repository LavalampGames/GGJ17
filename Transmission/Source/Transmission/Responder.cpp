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

	responder_text_ = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Response Text"));
	responder_text_->SetVisibility(false);
	responder_text_->SetTextRenderColor(FColor(0, 0, 0, 1));
	responder_text_->SetXScale(0.5f);
	responder_text_->SetYScale(0.5f);
	responder_text_->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	responder_text_->SetupAttachment(responder_mesh_);

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

	if (response_timer_ < 4.0f)
	{
		response_timer_ += DeltaTime;
		if (response_timer_ >= 4.0f)
		{
			responder_text_->SetVisibility(false);
		}
	}
}

void AResponder::DisplayAvailableResponses()
{
	
}

void AResponder::DisplayResponseText(FText response_text)
{
	responder_text_->SetText(response_text);
	responder_text_->SetVisibility(true);
	response_timer_ = 0.0f;
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
