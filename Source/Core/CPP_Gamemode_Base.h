// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_Widget_to_GM.h"
#include "GameFramework/GameModeBase.h"
#include "CPP_Gamemode_Base.generated.h"

/**
 * 
 */
UCLASS()
class TEST_HORREUR_API ACPP_Gamemode_Base : public AGameModeBase, public ICPP_Widget_to_GM
{
	GENERATED_BODY()
protected:

	virtual void ChangePawnClass_Implementation() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup Player")
	TSubclassOf<APawn> MyCharacter;

public:
	virtual void BeginPlay() override;
	virtual void DestroyPawn_Implementation() override;
};
