// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ResourceWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UResourceWidget::RefreshWidget(float InCurrent, float InMax)
{
	Bar->SetPercent(InCurrent / InMax);
	Current->SetText(FText::AsNumber(FMath::FloorToInt(InCurrent)));
	Max->SetText(FText::AsNumber(FMath::FloorToInt(InMax)));
}
