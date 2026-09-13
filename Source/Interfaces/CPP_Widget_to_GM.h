// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CPP_Widget_to_GM.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCPP_Widget_to_GM : public UInterface
{
	GENERATED_BODY()
};

class TEST_HORREUR_API ICPP_Widget_to_GM
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ChangePawnClass();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DestroyPawn();
};
