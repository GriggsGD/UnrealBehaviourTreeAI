// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TaggedWidget.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIOURTREEAI_API UTaggedWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	void SetTaggedActive(bool bActive);
protected:
	UPROPERTY( meta = (BindWidget))
	UTextBlock* TaggedTXT = nullptr;
};
