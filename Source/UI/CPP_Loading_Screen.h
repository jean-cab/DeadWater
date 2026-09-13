// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_Loading_Screen.generated.h"


UCLASS()
class TEST_HORREUR_API UCPP_Loading_Screen : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	TSoftObjectPtr<UWorld> MenuLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	TSoftObjectPtr<UWorld> GameLevel;

	UPROPERTY(Transient, meta = (BindWidgetAnim), BlueprintReadOnly, Category = "Animation")
	class UWidgetAnimation* FadeOut;

protected:
};
