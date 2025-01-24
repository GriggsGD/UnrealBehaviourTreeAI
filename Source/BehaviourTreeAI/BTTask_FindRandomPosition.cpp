// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomPosition.h"

#include "NavigationSystem.h"
#include "NPC_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindRandomPosition::UBTTask_FindRandomPosition(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Random Position in NavMesh";
}

EBTNodeResult::Type UBTTask_FindRandomPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const ctrl = Cast<ANPC_Controller>(OwnerComp.GetAIOwner()))
	{
		if (auto* const npc = ctrl->GetPawn())
		{
			auto const Origin = npc->GetActorLocation();

			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation Pos;
				if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, Pos))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Pos.Location);
				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
