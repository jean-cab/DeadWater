// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_Actor_to_Actor.h"
#include "GameFramework/Actor.h"
#include "CPP_Boat.generated.h"


UENUM(Blueprintable)
enum class EVelocityState : uint8
{
	Accel,
	Decel,
};

UCLASS()
class TEST_HORREUR_API ACPP_Boat : public AActor, public ICPP_Actor_to_Actor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Boat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	float CurrentSpeed = 0.f;

	UPROPERTY()
	float TargetSpeed = -800.f;

	UPROPERTY()
	float InterpolationSpeed = 0.5f;

	UPROPERTY()
	FTimerHandle WaitBeforeDecelerate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	EVelocityState VelocityState = EVelocityState::Accel;

	UPROPERTY(BlueprintReadWrite, Category = "Default")
	TObjectPtr<UMaterialInstanceDynamic> CabinMat;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	TObjectPtr<UStaticMeshComponent> MainBoatPiece;

	UFUNCTION()
	void OnAnimationStarted();

	UFUNCTION()
	void SetNewVelocity();

	UFUNCTION(BlueprintPure, Category = "Math")
	float NoiseLight() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Animation")
	void StartTimeline();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartCrochetage();
};
