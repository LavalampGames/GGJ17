#pragma once

#include "CoreMinimal.h"
#include "Response.h"
#include "Stimulus.h"
#include "GameFramework/Actor.h"
#include "Sequence.generated.h"

class AGameEvent;

UCLASS()
class TRANSMISSION_API ASequence : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASequence();

	/**
	* Logic that must be processed based on stimulus passed to a sequence
	* Outputs an array of valid responses that the player can use
	*/
	UFUNCTION(BlueprintCallable, Category = "Sequence Management")
	virtual void SequenceBegin(AStimulus* stimulus);

	/**
	* Logic that must be processed based on response that the player selects
	*/
	UFUNCTION(BlueprintCallable, Category = "Sequence Management")
	virtual void SequenceResolve(AResponse* response);

	/**
	* Logic that must be processed if the player does not respond in any way
	*/
	UFUNCTION(BlueprintCallable, Category = "Sequence Management")
	virtual void SequenceResolveNoResponse();

	/**
	* Clean up all responses created by this sequence
	*/
	UFUNCTION(BlueprintCallable, Category = "Response Management")
	void CleanupResponses();

	/**
	* Set the parent event of this sequence
	*/
	UFUNCTION(BlueprintCallable, Category = "Sequence Management")
	void SetParentEvent(AGameEvent* parent_event);

	/**
	* Get the parent event of this sequence
	*/
	UFUNCTION(BlueprintCallable, Category = "Sequence Management")
	AGameEvent* GetParentEvent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	/**
	* Some events may be time sensitive so should keep track of how long they have existed for
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sequence Management")
	float expiry_time_;

	float response_wait_timer_;
	
	/**
	* Track the parent event for this sequence so it can be informed when execution is complete
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sequence Management")
	AGameEvent* parent_event_;

	/**
	* Track responses created by this sequence for deletion
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Response Management")
	TArray<AResponse*> responses_;

	/**
	* Track stimulus created for this sequence for deletion
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sequence Management")
	AStimulus* stimulus_;
};
