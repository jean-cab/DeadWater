// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Turn_Light_Off.h"
#include "Components/RectLightComponent.h"
#include "Engine/StaticMeshActor.h"


// Sets default values
ACPP_Turn_Light_Off::ACPP_Turn_Light_Off()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	RootComponent = BoxComponent;
}

// Called when the game starts or when spawned
void ACPP_Turn_Light_Off::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACPP_Turn_Light_Off::OnOverlaped);
	if (Luminaire)
	{
		UMaterialInterface* TempMat = Luminaire->GetStaticMeshComponent()->GetMaterial(1);
		LuminaireMaterial = Luminaire->GetStaticMeshComponent()->CreateDynamicMaterialInstance(1, TempMat, NAME_None);
	}	
}

// Called every frame
void ACPP_Turn_Light_Off::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPP_Turn_Light_Off::OnOverlaped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Boat") && IsValid(LightTurnOff))
	{
		LightTurnOff->RectLightComponent->SetIntensity(0.0f);
		if (LuminaireMaterial)
		{
			LuminaireMaterial->SetScalarParameterValue("Emissive Multiplier", 0);
		}
	}
}
