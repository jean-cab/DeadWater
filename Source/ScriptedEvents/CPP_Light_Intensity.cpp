// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Light_Intensity.h"
#include "Components/PointLightComponent.h"

// Sets default values for this component's properties
UCPP_Light_Intensity::UCPP_Light_Intensity()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCPP_Light_Intensity::BeginPlay()
{
	Super::BeginPlay();
	Seed = FMath::RandRange(0.f, 10000.f);
	if (const AActor* Owner = GetOwner(); Owner)
	{
		TargetLight = Owner->FindComponentByClass<UPointLightComponent>();
	}
}


// Called every frame
void UCPP_Light_Intensity::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TargetLight)
	{
		const float Time = GetWorld()->GetTimeSeconds() + Seed;
		const float Noise = FMath::PerlinNoise1D(Time * FlickerSpeed);
		const float NewIntensity = FMath::GetMappedRangeValueClamped(FVector2D(-1.f, 1.f), FVector2D(MinIntensity, MaxIntensity), Noise);
		TargetLight->SetIntensity(NewIntensity);
	}
}

