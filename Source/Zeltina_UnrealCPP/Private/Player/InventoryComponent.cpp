// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Slots.SetNum(InventorySize);	//	인벤토리 크기만큼 빈 슬롯 만들기
	
}

int32 UInventoryComponent::AddItem(UItemDataAsset* InItemData, int32 InCount)
{
	return int32();
}

void UInventoryComponent::SetItemAtIndex(int32 InSlotIndex, UItemDataAsset* InItemData, int32 InCount)
{
	if (IsValidIndex(InSlotIndex))
	{
		FInvenSlot& TargetSlot = Slots[InSlotIndex];

		TargetSlot.ItemData = InItemData;
		TargetSlot.SetCount(InCount);	// InCount가 0이하면 자동 Clear

	}

}

void UInventoryComponent::UpdateSlotCount(int32 InSlotIndex, int32 InDeltaCount)
{
	if (IsValidIndex(InSlotIndex))
	{
		FInvenSlot& TargetSlot = Slots[InSlotIndex];
		if (TargetSlot.IsEmpty())	// 슬롯이 비어있으면 변화할 수 없음
		{
			return;
		}
		int32 NewCount = TargetSlot.GetCount() + InDeltaCount;
		SetItemAtIndex(InSlotIndex, TargetSlot.ItemData, NewCount);

	}
}

void UInventoryComponent::ClearSlotAtIndex(int32 InSlotIndex)
{
}

const FInvenSlot& UInventoryComponent::GetSlotData(int32 InSlotIndex) const
{
	check(IsValidIndex(InSlotIndex));
	/*
	* check	 : 거짓이면 프로그램 종료. shipping 빌드에 포함안됨
	* verify : 거짓이면 프로그램 종료. shipping 빌드에 포함됨(검사는 안함)
	* ensure : 거짓이면 로그 출력하고 계속. shipping 빌드에 포함됨
	*/
	return Slots[InSlotIndex];
}



