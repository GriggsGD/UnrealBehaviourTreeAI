// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChasePlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviourTreeAI/NPC.h"
#include "BehaviourTreeAI/NPC_Controller.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Chase Player";
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetBlackboardComponent()->GetValueAsBool("IsTagged"))
	{
		return EBTNodeResult::Succeeded;
	}
	if (auto* const ctrl = Cast<ANPC_Controller>(OwnerComp.GetAIOwner()))
	{
		if (auto* const NPC = Cast<ANPC>(ctrl->GetPawn()))
		{
			NPC->SetIsSearching(false);
		}
		if (OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(ctrl, OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey()));

			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
