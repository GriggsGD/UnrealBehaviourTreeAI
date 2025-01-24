// Fill out your copyright notice in the Description page of Project Settings.


#include "TaggedWidget.h"

void UTaggedWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTaggedWidget::SetTaggedActive(bool bActive)
{
	TaggedTXT->SetOpacity(bActive ? 255 : 0);
}
