// Fill out your copyright notice in the Description page of Project Settings.


#include "TagNotifyState.h"

#include "BTAICharacterBase.h"

void UTagNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABTAICharacterBase* const chara = Cast<ABTAICharacterBase>(MeshComp->GetOwner()))
		{
			chara->AttackStart();
		}
	}
}

void UTagNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABTAICharacterBase* const chara = Cast<ABTAICharacterBase>(MeshComp->GetOwner()))
		{
			chara->AttackEnd();
		}
	}
}
