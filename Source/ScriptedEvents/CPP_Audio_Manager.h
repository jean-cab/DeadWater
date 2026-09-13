// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_Actor_to_Actor.h"
#include "GameFramework/Actor.h"
#include "CPP_Audio_Manager.generated.h"

class ACPP_Sound_swim;
class AAmbientSound;

UCLASS()
class TEST_HORREUR_API ACPP_Audio_Manager : public AActor, public ICPP_Actor_to_Actor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Audio_Manager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Sound")
	TArray<TObjectPtr<AAmbientSound>> FoxScream;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Sound")
	TArray<TObjectPtr<AAmbientSound>> OwlScream;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Sound")
	TObjectPtr<USoundBase> Music;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Sound")
	TObjectPtr<USoundBase> Wind;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Sound")
	TObjectPtr<AAmbientSound> JumpIntoLake;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Sound")
	TObjectPtr<ACPP_Sound_swim> SwimActor;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Sound")
	TObjectPtr<USoundClass> AudioClass;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Sound")
	TObjectPtr<USoundMix> AudioMix;

	UPROPERTY()
	FTimerHandle TimerForOwl;

	UPROPERTY()
	FTimerHandle TimerForFox;

	UPROPERTY()
	FTimerHandle TimerForExtract;

	UPROPERTY()
	float TimeForOwl = 2.f;

	UPROPERTY()
	float TimeForFox = 5.f;

	UFUNCTION()
	void LaunchOwlSounds();

	UFUNCTION()
	void LaunchFoxSounds();

	UFUNCTION()
	void StartSwimActor();

	UFUNCTION()
	void StopSwimActor();

	UFUNCTION()
	void AfterTimer();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "Default")
	void StartJump();

	UFUNCTION()
	void StartMusic() const;
};
