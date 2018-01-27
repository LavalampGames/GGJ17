// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Response.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Responder.generated.h"

UCLASS()
class TRANSMISSION_API AResponder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResponder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	* Displays to the player available responses using this reponder
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Response Management")
	void DisplayAvailableResponses();
	
	/**
	* Add responses to this responder
	*/
	UFUNCTION(BlueprintCallable, Category = "Response Management")
	void AddResponse(AResponse* response);

	/**
	* Add responses to this responder
	*/
	UFUNCTION(BlueprintCallable, Category = "Response Management")
	void AddResponses(TArray<AResponse*> responses);

	/**
	* Remove a response from this responder
	*/
	UFUNCTION(BlueprintCallable, Category = "Response Management")
	void RemoveResponse(AResponse* response);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Response Management")
	TArray<AResponse*> available_responses_;
	
};
