// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Trigger_Sound.h"
#include "Components/BoxComponent.h"
#include "CPP_Audio_Manager.h"


// Sets default values
ACPP_Trigger_Sound::ACPP_Trigger_Sound()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(FName("BoxTrigger"));
	RootComponent = BoxTrigger;
}

// Called when the game starts or when spawned
void ACPP_Trigger_Sound::BeginPlay()
{
	Super::BeginPlay();
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACPP_Trigger_Sound::OnBeginOverlap);
	
}

// Called every frame
void ACPP_Trigger_Sound::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPP_Trigger_Sound::OnBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("Boat")) && IsValid(Audio_Manager))
	{
		Audio_Manager->StartJump();
		Audio_Manager->StartMusic();
	}
}

