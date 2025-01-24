// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RunAway.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviourTreeAI/NPC.h"
#include "GeometryCollection/Facades/CollectionConstraintOverrideFacade.h"

UBTTask_RunAway::UBTTask_RunAway(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Run Away");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_RunAway::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey()))
	{
		return EBTNodeResult::Succeeded;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsBool("InPursuit", false);
	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
	if (!Target)
	{
		return EBTNodeResult::Failed;
	}
	APawn* NPC = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (!NPC)
	{
		return EBTNodeResult::Failed;
	}
	Cast<ANPC>(NPC)->SetIsSearching(false);
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!NavSystem)
	{
		return EBTNodeResult::Failed;
	}
	
	FVector FleeDirection = (NPC->GetActorLocation() - Target->GetActorLocation()).GetSafeNormal();
	
	FVector FleeLocation = NPC->GetActorLocation() + FleeDirection * FleeDistance;

	FNavLocation ProjectedLocation;
	if (NavSystem->ProjectPointToNavigation(FleeLocation, ProjectedLocation))
	{
		MoveRequestID = OwnerComp.GetAIOwner()->MoveToLocation(ProjectedLocation.Location, -1.0f, true, true, false, true, 0, true);
		if (MoveRequestID.IsValid())
		{
			bIsMoving = true;
			TargetPos = ProjectedLocation.Location;
			return EBTNodeResult::InProgress;
		}
		return EBTNodeResult::Failed;
	}
	FNavLocation RandomNavLoc;

	if (NavSystem->GetRandomPointInNavigableRadius(NPC->GetActorLocation(), FleeDistance, RandomNavLoc))
	{
		OwnerComp.GetAIOwner()->MoveToLocation(RandomNavLoc.Location);
		bIsMoving = true;
		TargetPos = RandomNavLoc.Location;
		return EBTNodeResult::InProgress;
	}
	UE_LOG(LogTemp, Warning, TEXT("Run Away From Player: Could not project location on NavMesh!"));
	return EBTNodeResult::Failed;
}

void UBTTask_RunAway::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsMoving)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	APawn* NPC = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());

	if (NPC)
	{
		FVector CurrVelocity = NPC->GetVelocity();
		
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
	}
	if (FVector::Dist(NPC->GetActorLocation(), TargetPos) <= AcceptanceDistance)
	{
		TimeSpentStuck = 0.0f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	
}

void UBTTask_RunAway::OnTimeout(UBehaviorTreeComponent& OwnerComp)
{
	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
}
