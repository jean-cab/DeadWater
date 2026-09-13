// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Sound_swim.generated.h"

class USphereComponent;

UENUM(Blueprintable)
enum class EArrivedType : uint8
{
	Left UMETA(DisplayName = "Left"),
	Back UMETA(DisplayName = "Back"),
	Right UMETA(DisplayName = "Right"),
	Max UMETA(Hidden),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwimIsEnd);


UCLASS()
class TEST_HORREUR_API ACPP_Sound_swim : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Sound_swim();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	TObjectPtr<UAudioComponent> Transmitter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Sounds")
	TObjectPtr<USoundBase> SwimSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Sounds")
	TObjectPtr<USoundBase> ExtractWaterSound;

	UPROPERTY()
	FTimerHandle Th_Swim;

	UPROPERTY()
	int32 CountTimer;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	TObjectPtr<USphereComponent> Detection;

	

	UFUNCTION()
	void LaunchSound();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void StartSwimSequence();

	UFUNCTION()
	void StartExtractSound() const;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnSwimIsEnd OnSwimEnd;
private:

	UPROPERTY()
	FVector TargetLocation;

	UPROPERTY()
	bool bIsSwimming;

	UPROPERTY()
	TObjectPtr<AActor> BoatActor;

	UPROPERTY()
	int32 RandomEnumNumber;

	UPROPERTY()
	float BurstSpeed = 1200.f;

	UPROPERTY()
	FVector Direction;

	UPROPERTY()
	float CurrentSpeed;
	
	UFUNCTION()
	void DetectionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
