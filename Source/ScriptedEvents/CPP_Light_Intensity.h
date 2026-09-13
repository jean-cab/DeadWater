// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_Light_Intensity.generated.h"

class UPointLightComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TEST_HORREUR_API UCPP_Light_Intensity : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCPP_Light_Intensity();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	float Seed;

	UPROPERTY()
	UPointLightComponent* TargetLight;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Candle Settings", meta = (ClampMin = 0.0f, ClampMax = 60.0f))
	float MinIntensity = 60.f;

	UPROPERTY(EditAnywhere, Category = "Candle Settings", meta = (ClampMin = 61.0f, ClampMax = 160.0f))
	float MaxIntensity = 160.f;

	UPROPERTY(EditAnywhere, Category = "Candle Settings")
	float FlickerSpeed = 7.f;
};
