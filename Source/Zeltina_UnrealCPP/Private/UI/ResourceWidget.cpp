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

#if WITH_EDITOR
// UObject 멤버 변수에 변화가 있은 후에 자동 실행되는 함수
void UResourceWidget::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName propertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (propertyName == GET_MEMBER_NAME_CHECKED(UResourceWidget, FillColor))	// UResourceBarWidget의 FillColor가 변경되었을 때만 처리
	{
		BackgroundColor = FillColor;	// Background를 FillColor와 같은 색으로 알파만 0.2로 설정.
		BackgroundColor.A = 0.2f;
	}
}
#endif

void UResourceWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	Bar->SetFillColorAndOpacity(FillColor); // 채우기 색 적용

	// 배경 색 적용
	FProgressBarStyle style = Bar->GetWidgetStyle();
	style.BackgroundImage.TintColor = BackgroundColor;
	Bar->SetWidgetStyle(style);
}
