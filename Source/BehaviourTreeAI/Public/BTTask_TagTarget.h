// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviourTreeAI/NPC.h"
#include "BTTask_TagTarget.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIOURTREEAI_API UBTTask_TagTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_TagTarget();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI|Melee", meta = (AllowPrivateAccess = "true"))
	float MeleeMaxAngle = 25.0f;
	
	bool AnimFinished(ANPC* const npc);

	bool AnimPlayed = false;

	bool IsFacingTarget(AActor* AIActor, AActor* TargetActor, float AngleThreshold = 30.0f) const;
};
