// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameEvent.generated.h"

class ASequence;
class AGameGroup;

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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Sequence Management")
	void BeginEvent();

	/**
	* Once a sequence is complete we should clean it up and move to the next sequence
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Sequence Management")
	void ProgressEvent();

	/**
	* Generic events should also be able to resolve in the background without player input
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event Management")
	void BackgroundResolveEvent();

	/**
	* Calculate multiplier for event occuring
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event Management")
	float CalculateEventMultiplier();

public:
	TArray<AGameGroup*> associated_groups_;

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

	/**
	* Multiplier for the likelihood of this event occuring
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Management")
	float event_multiplier_;
};
