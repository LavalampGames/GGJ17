// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameEvent.generated.h"

class ASequence;
UCLASS()
class TRANSMISSION_API AGameEvent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameEvent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	* Sets up sequences that are used by this event
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Sequence Management")
	void BeginEvent();

	/**
	* Once a sequence is complete we should clean it up and move to the next sequence
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Sequence Management")
	void ProgressEvent();

protected:

	/**
	* The sequences that make up this event
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sequence Management")
	TArray<ASequence*> event_sequences_;

	/**
	* The index of the sequence that is currently being executed
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sequence Management")
	int current_sequence_index_;
};
