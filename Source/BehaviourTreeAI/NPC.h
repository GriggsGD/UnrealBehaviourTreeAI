// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTAICharacterBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "TagInterface.h"
#include "NPC.generated.h"

UCLASS()
class BEHAVIOURTREEAI_API ANPC : public ABTAICharacterBase, public ITagInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();

	UBehaviorTree* GetBehaviorTree() const;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Animation|AI")
	void SetIsSearching(bool bIsSearching);

	virtual void TagAttack_Implementation() override;

	UAnimMontage* GetMontage() const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BT;
	
private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Animation|AI", meta = (AllowPrivateAccess = "true"))
	bool IsSearching = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|AI", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Montage;
};
