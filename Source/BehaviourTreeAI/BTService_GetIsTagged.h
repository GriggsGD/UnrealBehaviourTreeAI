// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_GetIsTagged.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIOURTREEAI_API UBTService_GetIsTagged : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_GetIsTagged();
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
