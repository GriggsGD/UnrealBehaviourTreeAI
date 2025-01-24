// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayerPosition.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPlayerPosition::UBTTask_FindPlayerPosition(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Player Position";
}

EBTNodeResult::Type UBTTask_FindPlayerPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetBlackboardComponent()->GetValueAsBool("IsTagged"))
	{
		return EBTNodeResult::Succeeded;
	}
	
	if (auto* const target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor")))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("InPursuit", true);
		FVector const PlayerPosition = target->GetActorLocation();
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("TargetActorLastPos", PlayerPosition);
		if (SearchRandom)
		{
			FNavLocation NavPos;
			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld())){
				if (NavSys->GetRandomPointInNavigableRadius(PlayerPosition, SearchRadius, NavPos))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), NavPos.Location);
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					return EBTNodeResult::Succeeded;
				}
			}
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPosition);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
