// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACPP_MyCharacter::ACPP_MyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	SpringCam = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	bUseControllerRotationYaw = false;
	if (CameraComponent && SpringCam)
	{
		SpringCam->SetupAttachment(GetCapsuleComponent());
		SpringCam->SetRelativeLocation(FVector(0.0f, 0.0f, 65.0f));
		SpringCam->bEnableCameraRotationLag = true;
		SpringCam->CameraRotationLagSpeed = 13.f;
		SpringCam->TargetArmLength = 0.1f;
		SpringCam->bUsePawnControlRotation = true;
		SpringCam->bDoCollisionTest = false;
		CameraComponent->SetupAttachment(SpringCam);
	}

}

// Called when the game starts or when spawned
void ACPP_MyCharacter::BeginPlay()
{
	Super::BeginPlay();
	const float MyStartingYaw = GetActorRotation().Yaw;
	if (APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0); CameraManager)
	{
		CameraManager->ViewYawMin = MyStartingYaw - 150.f;
		CameraManager->ViewYawMax = MyStartingYaw + 150.f;
	}
}

// Called every frame
void ACPP_MyCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_MyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACPP_MyCharacter::ToggleDoorOpen_Implementation(const bool bIsOpen)
{
	bDoorEvent = bIsOpen;
	if (!bSeeEvent)
	{
		GetWorldTimerManager().SetTimer(JumpScareHandle, this, &ACPP_MyCharacter::CanBeDead, 1.f, true);
	}
}

void ACPP_MyCharacter::SetSeeStatue_Implementation(const bool bIsSee)
{
	bSeeEvent = bIsSee;
	if (!bDoorEvent)
	{
		return;
	}
	if (bSeeEvent)
	{
		GetWorldTimerManager().ClearTimer(JumpScareHandle);
		SecondPass = 0;
	}
	else
	{
		if (!GetWorldTimerManager().IsTimerActive(JumpScareHandle))
		{
			GetWorldTimerManager().SetTimer(JumpScareHandle, this, &ACPP_MyCharacter::CanBeDead, 1.f, true);
		}
	}
}


void ACPP_MyCharacter::CanBeDead()
{
	SecondPass++;
	int32 PercentDeath = 0;

	if (SecondPass >= 15)
	{
		PercentDeath = 80;
	}
	else if (SecondPass >= 10)
	{
		PercentDeath = 50;
	}
	else if (SecondPass >= 6)
	{
		PercentDeath = 40;
	}
	else if (SecondPass >= 4)
	{
		PercentDeath = 20;
	}
	if (PercentDeath > 0)
	{
		if (const int32 Tirage = FMath::RandRange(1, 100); Tirage <= PercentDeath)
		{
			Dead();
			GetWorldTimerManager().ClearTimer(JumpScareHandle);
		}
	}
}

void ACPP_MyCharacter::StartHeartSound_Implementation()
{
	if (IsValid(HeartSound))
	{
		UGameplayStatics::PlaySound2D(this, HeartSound);
	}
}
