// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToLastKnowPos.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviourTreeAI/NPC.h"
#include "BehaviourTreeAI/NPC_Controller.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTask_MoveToLastKnowPos::UBTTask_MoveToLastKnowPos(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Move To Last Known Position");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MoveToLastKnowPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!GetWorld()){ FinishLatentTask(OwnerComp, EBTNodeResult::Failed); return EBTNodeResult::Failed; }
	FVector SearchPos = ANPC_Controller::FindClosestNavigablePosition(GetWorld(), OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey()), FVector::One() * NavSearchExtent);

	if (SearchPos == FVector::ZeroVector)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	if (auto* const ctrl = Cast<ANPC_Controller>(OwnerComp.GetAIOwner()))
	{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(ctrl, OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey()));

	}
	else{FinishLatentTask(OwnerComp, EBTNodeResult::Failed); return EBTNodeResult::Failed;}
	if (auto* const NPC = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		NPC->SetIsSearching(true);
	}
	return EBTNodeResult::InProgress;
}

void UBTTask_MoveToLastKnowPos::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (auto* const npcPawn = OwnerComp.GetAIOwner()->GetPawn())
	{
		FVector CurrVelocity = npcPawn->GetVelocity();
		
		if (CurrVelocity.Size() <= StuckSpeedThreshold)
		{
			TimeSpentStuck += DeltaSeconds;
        
			if (TimeSpentStuck >= MaxStuckTime)
			{
				bIsStuck = true;
				OnTimeout(OwnerComp);
			}
		}
		else
		{
			TimeSpentStuck = 0.0f;
		}
		
		if (FVector::Dist(npcPawn->GetActorLocation(), OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey())) <= AcceptanceDistance)
		{
			TimeSpentStuck = 0.0f;
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
	

	
}

void UBTTask_MoveToLastKnowPos::OnTimeout(UBehaviorTreeComponent& OwnerComp)
{
	/*if (auto* const NPC = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		NPC->SetIsSearching(false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("InPursuit", false);
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}*/
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

