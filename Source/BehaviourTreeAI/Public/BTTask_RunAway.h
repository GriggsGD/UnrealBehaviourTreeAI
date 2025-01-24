// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_RunAway.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIOURTREEAI_API UBTTask_RunAway : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UBTTask_RunAway(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	private:
	UPROPERTY(EditAnywhere, Category = "AI")
	float FleeDistance = 500.0f;

	FAIRequestID MoveRequestID;
	
	

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Search", meta = (AllowPrivateAccess = "true"))
	float AcceptanceDistance = 100.0f;

	bool bIsMoving;
	
	void OnTimeout(UBehaviorTreeComponent& OwnerComp);

	//Movement timeout variables
	float TimeSpentStuck = 0.0f;

	bool bIsStuck = false;

	UPROPERTY(EditAnywhere, Category = "AI|Movement")
	float StuckSpeedThreshold = 10.0f; 

	UPROPERTY(EditAnywhere, Category = "AI|Movement")
	float MaxStuckTime = 5.0f;

	FVector TargetPos;
};
