// Fill out your copyright notice in the Description page of Project Settings.

#include "Response.h"
#include "Responder.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"
#include "TransmissionGameModeBase.h"

// Sets default values
AResponse::AResponse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	response_text_renderer_ = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Response Text"));
	response_text_renderer_->SetVisibility(false);
	response_text_renderer_->SetTextRenderColor(FColor(0, 0, 0, 1));
	response_text_renderer_->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	RootComponent = response_text_renderer_;

	OnClicked.AddDynamic(this, &AResponse::ClickResponse);
}

// Called when the game starts or when spawned
void AResponse::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResponse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AResponse::SetParentResponder(AResponder* responder)
{
	parent_responder_ = responder;
}

AResponder* AResponse::GetParentResponder()
{
	return parent_responder_;
}

void AResponse::SetResponseText(FText text)
{
	response_text_ = text;
	//response_text_renderer_->SetText(text);
}

void AResponse::ClickResponse(AActor * other, FKey key)
{
	ATransmissionGameModeBase* game_mode = (ATransmissionGameModeBase*)(GetWorld()->GetAuthGameMode());
	game_mode->SequenceResponse(this, ESequenceChannel(parent_responder_->response_channel_));
}