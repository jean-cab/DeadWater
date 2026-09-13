// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CPP_Actor_to_Actor.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCPP_Actor_to_Actor : public UInterface
{
	GENERATED_BODY()
};

class TEST_HORREUR_API ICPP_Actor_to_Actor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ToggleDoorOpen(bool bIsOpen);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetSeeStatue(bool bSeeDoor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartHeartSound();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ArmSound();
};
