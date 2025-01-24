// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "NPC_Controller.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIOURTREEAI_API ANPC_Controller : public AAIController
{
	GENERATED_BODY()

public:
	explicit ANPC_Controller(FObjectInitializer const& FObjectInitializer);

	UFUNCTION()
	static FVector FindClosestNavigablePosition(UWorld* World, const FVector& InputPosition, const FVector& SearchExtent = FVector(100.0f, 100.0f, 100.0f));
protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	class UAISenseConfig_Sight* SightConfig;

	void SetupPerceptionSys();

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);

	
};
