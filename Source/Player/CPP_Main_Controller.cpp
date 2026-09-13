// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Main_Controller.h"
#include "CPP_HUD_Main.h"
#include "EnhancedInputComponent.h"
#include "CPP_MainPlayerCameraManager.h"
#include "CPP_Actor_to_Actor.h"
#include "Blueprint/UserWidget.h"


ACPP_Main_Controller::ACPP_Main_Controller()
{
	PlayerCameraManagerClass = ACPP_MainPlayerCameraManager::StaticClass();
}

void ACPP_Main_Controller::BeginPlay()
{
	Super::BeginPlay();
}

void ACPP_Main_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(InputLook, ETriggerEvent::Triggered, this, &ACPP_Main_Controller::OnLook_Implementation);
	}
}

void ACPP_Main_Controller::SetFocusInput()
{
	if (const ACPP_HUD_Main* GameHUD = Cast<ACPP_HUD_Main>(GetHUD()); GameHUD)
	{
		if (GameHUD->WidgetToFocus)
		{
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(GameHUD->WidgetToFocus->TakeWidget());
			SetInputMode(InputMode);
			SetShowMouseCursor(true);
		}
	}
}

void ACPP_Main_Controller::SwitchInput_Implementation()
{
	const FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	SetShowMouseCursor(false);
	SetupInput();
}

void ACPP_Main_Controller::OnLook_Implementation(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	GetPawn()->AddControllerYawInput(LookAxisVector.X);
	GetPawn()->AddControllerPitchInput(LookAxisVector.Y);
	const FRotator CameraRotation = PlayerCameraManager->GetCameraRotation();
	if (const float YawRot = CameraRotation.Yaw; YawRot >= -60.f && YawRot <= -30.f)
	{
		ICPP_Actor_to_Actor::Execute_SetSeeStatue(GetPawn(), true);
	}
	else
	{
		ICPP_Actor_to_Actor::Execute_SetSeeStatue(GetPawn(), false);
	}
}