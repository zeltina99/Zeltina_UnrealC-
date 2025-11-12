// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainHudWidget.h"
#include "Player/ActionCharacter.h"
#include "Player/ResourceComponent.h"
#include "UI/ResourceWidget.h"

void UMainHudWidget::NativeConstruct()
{
	AActionCharacter* player = Cast<AActionCharacter>(GetOwningPlayerPawn());
	if (player && player->GetResourceComponent())
	{
		UResourceComponent* resource = player->GetResourceComponent();
		resource->OnHealthChanged.AddUObject(HealthBar.Get(), &UResourceWidget::RefreshWidget);		//	블루프린트 X
		resource->OnStaminaChanged.AddDynamic(StaminaBar.Get(), &UResourceWidget::RefreshWidget);	//	블루프린트 O

		HealthBar->RefreshWidget(resource->GetCurrentHealth(), resource->GetMaxHealth());
		StaminaBar->RefreshWidget(resource->GetCurrentStamina(), resource->GetMaxStamina());
	}

}