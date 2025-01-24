// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
//#include "BehaviourTree/BehaviorTree.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

UBehaviorTree* ANPC::GetBehaviorTree() const
{
	return BT;
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();

	SetIsTagged(true);
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::SetIsSearching(bool bIsSearching)
{
	IsSearching = bIsSearching;
}

void ANPC::TagAttack_Implementation()
{
	if (Montage)
	{
		PlayAnimMontage(Montage);
	}
}

UAnimMontage* ANPC::GetMontage() const
{
	return Montage;
}

