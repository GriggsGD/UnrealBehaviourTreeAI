// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsTargetInMeleeRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviourTreeAI/NPC.h"

UBTService_IsTargetInMeleeRange::UBTService_IsTargetInMeleeRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Target in Melee Range");
}

void UBTService_IsTargetInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const * npc = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
	auto const * target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), target ? npc->GetDistanceTo(target) <= MeleeRange : false);
}
