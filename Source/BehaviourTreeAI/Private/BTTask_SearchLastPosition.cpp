// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SearchLastPosition.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviourTreeAI/NPC.h"

UBTTask_SearchLastPosition::UBTTask_SearchLastPosition(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Search Last Known Target Position");
	bNotifyTick = true;
	
}

EBTNodeResult::Type UBTTask_SearchLastPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (auto* const NPC = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		if (!bAnimPlayed)
		{
			if (AnimationToPlay)
			{
				if (UAnimInstance* AnimInstance = NPC->GetMesh()->GetAnimInstance())
				{
					AnimInstance->Montage_Play(AnimationToPlay);
				}
				bAnimPlayed = true;
			}
		}
	}
	return EBTNodeResult::InProgress;
}

void UBTTask_SearchLastPosition::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	if (true) //Animation finished
	{
		if (auto* const NPC = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn()))
		{
			NPC->SetIsSearching(false);
			UAnimInstance* AnimInstance = NPC->GetMesh()->GetAnimInstance();
			if (bAnimPlayed && AnimInstance && !AnimInstance->IsAnyMontagePlaying())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool("InPursuit", false);
				bAnimPlayed = false;
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}
	}
}
