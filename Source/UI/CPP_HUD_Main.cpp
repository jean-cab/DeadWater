// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_HUD_Main.h"
#include "Blueprint/UserWidget.h"
#include "CPP_Loading_Screen.h"
#include "CPP_Main_Menu.h"
#include "CPP_Main_Controller.h"
#include "CPP_Screen_Dead.h"


void ACPP_HUD_Main::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ACPP_Main_Controller>(GetOwningPlayerController());
	if (PlayerController)
	{
		if (MainScreenClass && !IsValid(MainScreenWidget))
		{
			MainScreenWidget = CreateWidget<UCPP_Main_Menu>(PlayerController, MainScreenClass);
			if (MainLoadScreenClass && !IsValid(MainLoadScreenWidget))
			{
				MainLoadScreenWidget = CreateWidget<UCPP_Loading_Screen>(PlayerController, MainLoadScreenClass);
				MainLoadScreenWidget->AddToViewport();
				MainLoadScreenWidget->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
		if (MainScreenWidget)
		{
			MainScreenWidget->AddToViewport();
			WidgetToFocus = MainScreenWidget;
			PlayerController->SetFocusInput();
		}
		if (DeadScreenClass && !IsValid(DeadScreen))
		{
			DeadScreen = CreateWidget<UCPP_Screen_Dead>(PlayerController, DeadScreenClass);
			DeadScreen->AddToViewport();
			DeadScreen->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void ACPP_HUD_Main::MainScreenFinishAnim_Implementation()
{
	MainScreenWidget->SetVisibility(ESlateVisibility::Collapsed);
	MainLoadScreenWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void ACPP_HUD_Main::SwitchDeadScreenToMainScreen_Implementation()
{
	DeadScreen->SetVisibility(ESlateVisibility::Collapsed);
	MainScreenWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	WidgetToFocus = MainScreenWidget;
	PlayerController->SetFocusInput();
}

void ACPP_HUD_Main::ShowDeadWidget()
{
	DeadScreen->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	WidgetToFocus = DeadScreen;
	PlayerController->SetFocusInput();
}