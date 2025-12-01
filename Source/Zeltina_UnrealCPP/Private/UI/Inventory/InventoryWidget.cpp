// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryWidget.h"
#include "UI/Inventory/InventorySlotWidget.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "Player/InventoryComponent.h"


void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnCloseClicked);
	}

	
}

void UInventoryWidget::InitializeInventoryWidget(UInventoryComponent* InventoryComponent)
{
	if (InventoryComponent && SlotGridPanel)
	{
		TargetInventory = InventoryComponent;
		if (TargetInventory.IsValid())
		{
			int32 size = FMath::Min(SlotGridPanel->GetChildrenCount(), TargetInventory->GetInventorySize());

			for (int i = 0; i < size; i++)
			{
				FInvenSlot* slotData = TargetInventory->GetSlotData(i);
				UInventorySlotWidget* slotWidget = Cast<UInventorySlotWidget>(SlotGridPanel->GetChildAt(i));
				slotWidget->InitializeSlot(i, slotData);
			}
		}
	}
}

void UInventoryWidget::ClearInventoryWidget()
{
	TargetInventory = nullptr;
}

void UInventoryWidget::OnCloseClicked()
{
	OnInventoryCloseRequested.Broadcast();	// 닫힘 버튼이 눌려졌다는 것을 알림
}