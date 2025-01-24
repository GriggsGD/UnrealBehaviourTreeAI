// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_GetIsTagged.h"

#include "AIController.h"
#include "BTAICharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_GetIsTagged::UBTService_GetIsTagged()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Get is Tagged");
}

void UBTService_GetIsTagged::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto const * npc = Cast<ABTAICharacterBase>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), npc->GetIsTagged());
	}
}
