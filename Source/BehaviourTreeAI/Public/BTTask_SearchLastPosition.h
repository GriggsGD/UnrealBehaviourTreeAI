// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SearchLastPosition.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIOURTREEAI_API UBTTask_SearchLastPosition : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UBTTask_SearchLastPosition(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* AnimationToPlay;

	private:
	bool bAnimPlayed = false;
};


