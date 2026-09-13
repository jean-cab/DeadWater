// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Boat.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "CPP_Loading_Screen.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACPP_Boat::ACPP_Boat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	MainBoatPiece = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainBoatPiece"));
	if (IsValid(MainBoatPiece))
	{
		RootComponent = MainBoatPiece;
	}
}

// Called when the game starts or when spawned
void ACPP_Boat::BeginPlay()
{
	Super::BeginPlay();
	TArray<UUserWidget*> WidgetsFound;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), WidgetsFound, UCPP_Loading_Screen::StaticClass(), false);
	if (WidgetsFound.Num() > 0)
	{
		if (UCPP_Loading_Screen* Loading_Screen = Cast<UCPP_Loading_Screen>(WidgetsFound[0]); Loading_Screen)
		{
			FWidgetAnimationDynamicEvent MyAnimationDynamicEvent;
			MyAnimationDynamicEvent.BindUFunction(this, FName("OnAnimationStarted"));
			Loading_Screen->BindToAnimationEvent(Loading_Screen->FadeOut, MyAnimationDynamicEvent, EWidgetAnimationEvent::Started);
		}
	}
	
}

// Called every frame
void ACPP_Boat::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	switch (VelocityState)
	{
		{
			case EVelocityState::Accel :
			CurrentSpeed = FMath::FInterpTo(CurrentSpeed, TargetSpeed, DeltaTime, InterpolationSpeed);
			const FVector MovementAccel = FVector(CurrentSpeed * DeltaTime, 0.0f, 0.0f);
			AddActorLocalOffset(MovementAccel);
			break;
		}
		{
			case EVelocityState::Decel :
			CurrentSpeed = FMath::FInterpTo(CurrentSpeed, 0.0f, DeltaTime, InterpolationSpeed);
			const FVector MovementDecel = FVector(CurrentSpeed * DeltaTime, 0.0f, 0.0f);
			AddActorLocalOffset(MovementDecel);
			if (MovementDecel.IsNearlyZero(0.001))
			{
				SetActorTickEnabled(false);
			}
			break;
		}
	}
}

void ACPP_Boat::OnAnimationStarted()
{
	SetActorTickEnabled(true);
	GetWorld()->GetTimerManager().SetTimer(WaitBeforeDecelerate,this, &ACPP_Boat::SetNewVelocity, 12.f, false);
}

void ACPP_Boat::SetNewVelocity()
{
	VelocityState = EVelocityState::Decel;
	StartTimeline();
}

float ACPP_Boat::NoiseLight() const
{
	const float Time = UGameplayStatics::GetTimeSeconds(GetWorld());
	const float PerlinOutput = UKismetMathLibrary::PerlinNoise1D(Time * 10.f);
	return UKismetMathLibrary::MapRangeClamped(PerlinOutput, -1.f, 1.f, 0.f, 200.f);
}