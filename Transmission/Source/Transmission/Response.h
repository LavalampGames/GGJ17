// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Response.generated.h"
class AResponder;
UCLASS()
class TRANSMISSION_API AResponse : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResponse();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetParentResponder(AResponder* responder);

	UFUNCTION(BlueprintCallable, Category = "Response Management")
	inline AResponder* GetParentResponder() { return parent_responder_; }

protected:
	AResponder* parent_responder_;
};
