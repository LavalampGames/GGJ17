// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Response.h"
#include "RadioResponse.generated.h"

/**
 * 
 */
UCLASS()
class TRANSMISSION_API ARadioResponse : public AResponse
{
	GENERATED_BODY()

public:
	ARadioResponse();

	UFUNCTION(BlueprintCallable, Category = "Response Management")
	void SetResponseText(FString text) { response_text_ = text; }

protected:
	FString response_text_;
};
