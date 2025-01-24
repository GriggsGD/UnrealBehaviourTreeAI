// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TagInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UTagInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BEHAVIOURTREEAI_API ITagInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Tag" )
	void TagAttack();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Tag")
	bool GetIsTagged();
protected:
	bool IsTagged = false;
};
