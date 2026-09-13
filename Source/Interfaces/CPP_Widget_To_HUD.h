// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CPP_Widget_To_HUD.generated.h"

UENUM(Blueprintable)
enum class ESettingVisibility : uint8
{
	Show,
	Hide,
};

UINTERFACE(MinimalAPI)
class UCPP_Widget_To_HUD : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TEST_HORREUR_API ICPP_Widget_To_HUD
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void MainScreenFinishAnim();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SwitchDeadScreenToMainScreen();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ShowHideSettingMenu(ESettingVisibility Visibility);
};
