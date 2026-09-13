// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Audio_Manager.h"
#include "CPP_Sound_swim.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/AmbientSound.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundClass.h"

// Sets default values
ACPP_Audio_Manager::ACPP_Audio_Manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACPP_Audio_Manager::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(Wind))
	{
		UAudioComponent* WindSoundComponent = UGameplayStatics::SpawnSound2D(this, Wind, 0.5f, 1.f, 0.f, nullptr, false, false);
		if (IsValid(AudioClass) && IsValid(AudioMix))
		{
			UGameplayStatics::PopSoundMixModifier(GetWorld(), AudioMix);
		}
	}
	if (JumpIntoLake)
	{
		JumpIntoLake->GetAudioComponent()->OnAudioFinished.AddDynamic(this, &ACPP_Audio_Manager::StartSwimActor);
	}
	if (IsValid(SwimActor))
	{
		SwimActor->OnSwimEnd.AddDynamic(this, &ACPP_Audio_Manager::StopSwimActor);
	}
}

// Called every frame
void ACPP_Audio_Manager::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPP_Audio_Manager::StartJump()
{
	if (IsValid(JumpIntoLake))
	{
		JumpIntoLake->Play();
	}
	GetWorld()->GetTimerManager().SetTimer(TimerForOwl, this, &ACPP_Audio_Manager::LaunchOwlSounds, TimeForOwl, false);
	GetWorld()->GetTimerManager().SetTimer(TimerForFox, this, &ACPP_Audio_Manager::LaunchFoxSounds, TimeForFox, false);
}

void ACPP_Audio_Manager::LaunchOwlSounds()
{
	const int32 RandomTime = FMath::RandRange(15, 35);
	TimeForOwl = RandomTime;
	if (OwlScream.Num() == 0)
	{
		return;
	}
	if (const int32 RandomIndex = FMath::RandRange(0, OwlScream.Num() - 1); IsValid(OwlScream[RandomIndex]))
	{
		OwlScream[RandomIndex]->Play();
	}
	GetWorld()->GetTimerManager().SetTimer(TimerForOwl, this, &ACPP_Audio_Manager::LaunchOwlSounds, TimeForOwl, false);
}

void ACPP_Audio_Manager::LaunchFoxSounds()
{
	const int32 RandomTime = FMath::RandRange(20, 30);
	TimeForFox = RandomTime;
	if (FoxScream.Num() == 0)
	{
		return;
	}
	if (const int32 RandomIndex = FMath::RandRange(0, FoxScream.Num() - 1); IsValid(FoxScream[RandomIndex]))
	{
		FoxScream[RandomIndex]->Play();
	}
	GetWorld()->GetTimerManager().SetTimer(TimerForFox, this, &ACPP_Audio_Manager::LaunchFoxSounds, TimeForFox, false);
}

void ACPP_Audio_Manager::StartMusic() const
{
	UAudioComponent* HorrorSound = UGameplayStatics::SpawnSound2D(this, Music, 0.7f, 1.f, 0.f, nullptr, false, false);
}

void ACPP_Audio_Manager::StartSwimActor()
{
	if (IsValid(SwimActor))
	{
		SwimActor->StartSwimSequence();
		SwimActor->SetActorTickEnabled(true);
	}
}

void ACPP_Audio_Manager::StopSwimActor()
{
	GetWorldTimerManager().ClearAllTimersForObject(this);
	SwimActor->SetActorTickEnabled(false);
	GetWorldTimerManager().SetTimer(TimerForExtract, this, &ACPP_Audio_Manager::AfterTimer, 3.f, false);
}

void ACPP_Audio_Manager::AfterTimer()
{
	GetWorldTimerManager().ClearTimer(TimerForExtract);
	SwimActor->StartExtractSound();
}
