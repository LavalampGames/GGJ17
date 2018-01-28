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


	UFUNCTION(BlueprintCallable, Category = "Response Management" )
	void SetParentResponder(AResponder* responder);

	UFUNCTION(BlueprintCallable, Category = "Response Management")
	AResponder* GetParentResponder();
	
	UFUNCTION(BlueprintCallable, Category = "Response Management")
	void SetResponseText(FText text);

	/**
	* On click response function
	*/
	UFUNCTION()
	void ClickResponse(AActor* other, FKey key);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Response Managment")
	class UTextRenderComponent* response_text_renderer_;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Response Managment")
	FText response_text_;

protected:
	AResponder* parent_responder_;
	
};
