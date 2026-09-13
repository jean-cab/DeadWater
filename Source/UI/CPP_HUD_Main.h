// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_HUD_To_Controller.h"
#include "CPP_Widget_To_HUD.h"
#include "GameFramework/HUD.h"
#include "CPP_HUD_Main.generated.h"

class UCPP_Screen_Dead;
class UCPP_Loading_Screen;
class ACPP_Main_Controller;
class UCPP_Main_Menu;

UCLASS()
class TEST_HORREUR_API ACPP_HUD_Main : public AHUD, public ICPP_Widget_To_HUD, public ICPP_HUD_To_Controller
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void MainScreenFinishAnim_Implementation() override;
	virtual void SwitchDeadScreenToMainScreen_Implementation() override;

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCPP_Main_Menu> MainScreenClass;
	
	UPROPERTY(EditAnywhere)
    TSubclassOf<UCPP_Loading_Screen> MainLoadScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCPP_Screen_Dead> DeadScreenClass;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UCPP_Main_Menu> MainScreenWidget;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UCPP_Loading_Screen> MainLoadScreenWidget;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACPP_Main_Controller> PlayerController;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UCPP_Screen_Dead> DeadScreen;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* WidgetToFocus;

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void ShowDeadWidget();

	
};
