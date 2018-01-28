// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameEvent.h"
#include "GameFramework/Actor.h"
#include "GameLocation.generated.h"

UCLASS()
class TRANSMISSION_API AGameLocation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameLocation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "World Management")
	TArray<FString> GetCurrentAlerts() { return current_alerts_; }

	UFUNCTION(BlueprintCallable, Category = "World Management")
	FVector2D GetPosition() { return position_; }

	UFUNCTION(BlueprintCallable, Category = "World Management")
	void AddAlert(FString alert);

	UFUNCTION(BlueprintCallable, Category = "World Management")
	int ModifyFoodSupplies(int amount);

	UFUNCTION(BlueprintCallable, Category = "World Management")
	int ModifyMedicalSupplies(int amount);

	UFUNCTION(BlueprintCallable, Category = "World Management")
	int ModifyCombatSupplies(int amount);
protected:
	TArray<AGameEvent*> previous_events_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Management")
	FVector2D position_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Management")
	TArray<FString> current_alerts_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Management")
	float food_supply_level_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Management")
	float medical_supply_level_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Management")
	float combat_supply_level_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldManagement")
	float threat_level_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldManagement")
	float drop_timer_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldManagement")
	FString location_name_;
};
