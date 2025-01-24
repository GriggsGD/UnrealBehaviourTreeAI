// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MoveToLastKnowPos.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIOURTREEAI_API UBTTask_MoveToLastKnowPos : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit  UBTTask_MoveToLastKnowPos(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	void OnTimeout(UBehaviorTreeComponent& OwnerComp);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Search", meta = (AllowPrivateAccess = "true"))
	float AcceptanceDistance = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Search", meta = (AllowPrivateAccess = "true"))
	float NavSearchExtent = 500.0f;

	//Movement timeout variables
	float TimeSpentStuck = 0.0f;

	bool bIsStuck = false;

	UPROPERTY(EditAnywhere, Category = "AI|Movement")
	float StuckSpeedThreshold = 10.0f; 

	UPROPERTY(EditAnywhere, Category = "AI|Movement")
	float MaxStuckTime = 5.0f; 
};
