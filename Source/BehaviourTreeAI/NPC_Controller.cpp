// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_Controller.h"

#include "BehaviourTreeAICharacter.h"
#include "NavigationSystem.h"
#include "NPC.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ANPC_Controller::ANPC_Controller(FObjectInitializer const& FObjectInitializer)
{
	SetupPerceptionSys();
}

FVector ANPC_Controller::FindClosestNavigablePosition(UWorld* World, const FVector& InputPosition,
	const FVector& SearchExtent)
{
	if (!World)
	{
		return FVector::ZeroVector;
	}

	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
	if (!NavSystem)
	{
		return FVector::ZeroVector;
	}

	FNavLocation NavLocation;
	bool bFound = NavSystem->ProjectPointToNavigation(
		InputPosition,  // Input position to project
		NavLocation,    // Resulting closest position on NavMesh
		SearchExtent    // Search radius around the input position
	);

	return bFound ? NavLocation.Location : FVector::ZeroVector;
}

void ANPC_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ANPC* const npc = Cast<ANPC>(InPawn))
	{
		if (UBehaviorTree* const BTree = npc->GetBehaviorTree())
		{
			UBlackboardComponent* b;
			UseBlackboard(BTree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(BTree);
		}
	}
}

void ANPC_Controller::SetupPerceptionSys()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		SightConfig->SightRadius=500.0f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.0f;
		SightConfig->PeripheralVisionAngleDegrees = 90.0f;
		SightConfig->SetMaxAge(5.f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.0f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ANPC_Controller::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

void ANPC_Controller::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		if (auto* const PlChara = Cast<ABehaviourTreeAICharacter>(Actor))
		{
			GetBlackboardComponent()->SetValueAsObject("TargetActor", Actor);
			
		}
	}
	else
	{
		GetBlackboardComponent()->SetValueAsObject("TargetActor", nullptr);
	}
}
