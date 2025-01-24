// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BTAICharacterBase.generated.h"

UCLASS()
class BEHAVIOURTREEAI_API ABTAICharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ABTAICharacterBase();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool GetIsTagged() const;
	void SetIsTagged(bool isTagged);

	UPROPERTY()
	class UUserWidget* TaggedWidgetInstance;

	void ShowTaggedWidget();
	void HideTaggedWidget();

	void AttackStart() const;
	void AttackEnd() const;
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	bool bIsTagged;
private:
	UPROPERTY()
	class UWidgetComponent* WidgetComp;
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> WidgetClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", Meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* RightFistColBox;

	UFUNCTION()
	void OnTagOverlapBegin(
		UPrimitiveComponent* const OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* const OtherComp,
		int32 const OtherBodyIndex,
		bool const bFromSweep,
		FHitResult const& SweepResult);

	UFUNCTION()
	void OnTagOverlapEnd(
		UPrimitiveComponent* const OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* const OtherComp,
		int32 const OtherBodyIndex);
};


