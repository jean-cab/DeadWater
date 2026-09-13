// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Sound_swim.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CPP_Boat.h"

// Sets default values
ACPP_Sound_swim::ACPP_Sound_swim()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	Transmitter = CreateDefaultSubobject<UAudioComponent>(FName("Transmitter"));
	if (Transmitter)
	{
		RootComponent = Transmitter;
		Transmitter->SetMobility(EComponentMobility::Movable);
	}
	Detection = CreateDefaultSubobject<USphereComponent>(FName("Detection"));
	if (Detection)
	{
		Detection->SetupAttachment(Transmitter);
	}
}

// Called when the game starts or when spawned
void ACPP_Sound_swim::BeginPlay()
{
	Super::BeginPlay();
	Transmitter->SetSound(SwimSound);
	BoatActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACPP_Boat::StaticClass());
	Detection->OnComponentBeginOverlap.AddDynamic(this, &ACPP_Sound_swim::DetectionOverlapBegin);
	RandomEnumNumber = FMath::RandRange(0, static_cast<int32>(EArrivedType::Max) -1 );
}

// Called every frame
void ACPP_Sound_swim::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsValid(BoatActor))
	{
		return;
	}
	CurrentSpeed = FMath::FInterpTo(CurrentSpeed, 0.f, DeltaTime, 1.5f);
	if (CurrentSpeed < 0.5f)
	{
		return;
	}
	AddActorWorldOffset(Direction * CurrentSpeed * DeltaTime);
	if (const float DistanceToTarget = FVector::Dist(GetActorLocation(), TargetLocation); DistanceToTarget < 50.f)
	{
		if (OnSwimEnd.IsBound())
		{
			OnSwimEnd.Broadcast();
			GetWorldTimerManager().ClearAllTimersForObject(this);
		}
	}
}

void ACPP_Sound_swim::StartSwimSequence()
{
	const float NumAleatory01 = FMath::RandRange(1.5f, 2.f);
	GetWorldTimerManager().SetTimer(Th_Swim, this, &ACPP_Sound_swim::LaunchSound, NumAleatory01, true);
}


void ACPP_Sound_swim::LaunchSound()
{
	if (IsValid(SwimSound) && Transmitter->GetSound() == SwimSound)
	{
		if (IsValid(BoatActor))
		{
			const FVector LocalTargetLocation = BoatActor->GetActorLocation();
			const FVector BoatLocation = FVector(LocalTargetLocation.X, LocalTargetLocation.Y, GetActorLocation().Z);
			switch (const EArrivedType Selection = StaticCast<EArrivedType>(RandomEnumNumber); Selection)
			{
				case EArrivedType::Left:
				TargetLocation = (BoatLocation - (BoatActor->GetActorRightVector() * 300.f)) + (BoatActor->GetActorForwardVector() * 200.f);
				break;

				case EArrivedType::Right:
				TargetLocation = (BoatLocation + (BoatActor->GetActorRightVector() * 300.f)) + (BoatActor->GetActorForwardVector() * 200.f);
				break;

				case EArrivedType::Back:
				TargetLocation = (BoatLocation + (BoatActor->GetActorForwardVector() * 500.f));
				break;

				default:
				break;
			}
			Transmitter->Play();
			Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();
			CurrentSpeed = BurstSpeed;
		}
	}
}

void ACPP_Sound_swim::DetectionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag(FName("Boat")))
	{
		BurstSpeed = 600.f;
		if (GetWorldTimerManager().IsTimerActive(Th_Swim))
		{
			GetWorldTimerManager().ClearTimer(Th_Swim);
			const float TimeForTimer03 = FMath::RandRange(2.f, 2.5f);
			Transmitter->SetVolumeMultiplier(0.8f);
			Transmitter->SetPitchMultiplier(0.9f);
			GetWorldTimerManager().SetTimer(Th_Swim, this, &ACPP_Sound_swim::LaunchSound, TimeForTimer03, true);
		}
	}
}

void ACPP_Sound_swim::StartExtractSound() const
{
	Transmitter->SetPitchMultiplier(1.0f);
	Transmitter->SetVolumeMultiplier(1.0f);
	Transmitter->SetSound(ExtractWaterSound);
	if (Transmitter->GetSound() == ExtractWaterSound)
	{
		Transmitter->Play();
		ACPP_Boat* BoatCasted = Cast<ACPP_Boat>(BoatActor);
		if (!BoatCasted)
		{
			return;
		}
		Transmitter->OnAudioFinished.AddDynamic(BoatCasted, &ACPP_Boat::StartCrochetage);
	}
}