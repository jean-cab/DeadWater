// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_Widget_to_Controller.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "CPP_Main_Controller.generated.h"

class UInputAction;

UCLASS()
class TEST_HORREUR_API ACPP_Main_Controller : public APlayerController, public ICPP_Widget_to_Controller
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SwitchInput_Implementation() override;
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintImplementableEvent)
	void SetupInput();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Default")
	TObjectPtr<UInputAction> InputLook;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Default")
	TObjectPtr<UInputAction> InputUsed;


public:
	ACPP_Main_Controller();
	
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void SetFocusInput();

	UFUNCTION(BlueprintNativeEvent, Category = "Default")
	void OnLook(const FInputActionValue& Value);
	
};
