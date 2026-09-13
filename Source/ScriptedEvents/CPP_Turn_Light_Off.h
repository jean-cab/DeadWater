// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Engine/RectLight.h"
#include "GameFramework/Actor.h"
#include "CPP_Turn_Light_Off.generated.h"

class AStaticMeshActor;

UCLASS()
class TEST_HORREUR_API ACPP_Turn_Light_Off : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACPP_Turn_Light_Off();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	TObjectPtr<ARectLight> LightTurnOff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	TObjectPtr<AStaticMeshActor> Luminaire;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target")
	TObjectPtr<UMaterialInstanceDynamic> LuminaireMaterial;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlaped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
