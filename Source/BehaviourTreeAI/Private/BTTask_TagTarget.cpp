// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TagTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviourTreeAI/NPC.h"

UBTTask_TagTarget::UBTTask_TagTarget()
{
	NodeName = TEXT("Tag Target");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_TagTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetBlackboardComponent()->GetValueAsBool("IsTagged"))
	{
		return EBTNodeResult::Succeeded;
	}
	
	if (!OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey()))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	if (!IsFacingTarget(OwnerComp.GetAIOwner()->GetPawn(), Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor")), MeleeMaxAngle))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	auto* const npc = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
	npc->GetController()->StopMovement();
	if (auto* const iTag = Cast<ITagInterface>(npc))
	{
		iTag->Execute_TagAttack(npc);
		AnimPlayed = true;
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Succeeded;
}

void UBTTask_TagTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto* const npc = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (AnimPlayed && AnimFinished(npc))
	{
		AnimPlayed = false;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

bool UBTTask_TagTarget::AnimFinished(ANPC* const npc)
{
	return npc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npc->GetMontage());
}

bool UBTTask_TagTarget::IsFacingTarget(AActor* AIActor, AActor* TargetActor, float AngleThreshold) const
{
	if (!AIActor || !TargetActor)
	{
		return false;
	}

	FVector AILocation = AIActor->GetActorLocation();
	FVector AIFacingDirection = AIActor->GetActorForwardVector();
	FVector TargetPos = TargetActor->GetActorLocation();
	FVector DirectionToTarget = (TargetPos - AILocation).GetSafeNormal();
	
	float DotProduct = FVector::DotProduct(AIFacingDirection, DirectionToTarget);
	float ThresholdRadians = FMath::Cos(FMath::DegreesToRadians(AngleThreshold));

	return DotProduct >= ThresholdRadians;
}
