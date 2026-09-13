// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Gamemode_Base.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"


void ACPP_Gamemode_Base::BeginPlay()
{
	Super::BeginPlay();
}

void ACPP_Gamemode_Base::ChangePawnClass_Implementation()
{
	if (MyCharacter)
	{
		DefaultPawnClass = MyCharacter;
		if (AActor* PlayerStart = UGameplayStatics::GetActorOfClass(this, APlayerStart::StaticClass()); IsValid(PlayerStart))
		{
			RestartPlayerAtPlayerStart(GetWorld()->GetFirstPlayerController(), PlayerStart);
		}
	}
}

void ACPP_Gamemode_Base::DestroyPawn_Implementation()
{
	if (const APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0); IsValid(PC))
	{
		if (APawn* PlayerPawn = PC->GetPawn(); IsValid(PlayerPawn))
		{
			PlayerPawn->Destroy();
		}
	}
}
