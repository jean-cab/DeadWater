// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_Actor_to_Actor.h"
#include "CPP_MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TEST_HORREUR_API ACPP_MyCharacter : public ACharacter, public ICPP_Actor_to_Actor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_MyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void ToggleDoorOpen_Implementation(bool bIsOpen) override;
	virtual void SetSeeStatue_Implementation(bool bIsSee) override;
	virtual void StartHeartSound_Implementation() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Character")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Character")
	TObjectPtr<USpringArmComponent> SpringCam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<USoundBase> HeartSound;

	UPROPERTY()
	FTimerHandle JumpScareHandle;

	UPROPERTY()
	int32 SecondPass;

	UPROPERTY()
	bool bCanBeAttacked = true;

	UPROPERTY()
	bool bDoorEvent = false;

	UPROPERTY()
	bool bSeeEvent = false;

	UFUNCTION()
	void CanBeDead();

	UFUNCTION(BlueprintImplementableEvent)
	void Dead();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
