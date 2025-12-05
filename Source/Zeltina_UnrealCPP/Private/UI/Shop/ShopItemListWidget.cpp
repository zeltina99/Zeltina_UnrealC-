// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Shop/ShopItemListWidget.h"
#include "UI/Shop/ShopItemBuyWidget.h"
#include "Data/DataTableRows.h"
#include "Components/VerticalBox.h"

void UShopItemListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ItemBuyContainer)
	{
		int count = ItemBuyContainer->GetChildrenCount();
		ShopItems.Empty(count);
		for (int32 i = 0; i < count; i++)
		{
			UShopItemBuyWidget* itemWidget = Cast<UShopItemBuyWidget>(ItemBuyContainer->GetChildAt(i));
			ShopItems.Add(itemWidget);
		}
	}

}

void UShopItemListWidget::ResetItemList(UDataTable* ItemList)
{
	TArray<FShopData_TableRow*> allRows;
	ItemList->GetAllRows(TEXT("ShopDataTable"), allRows);
	for (const FShopData_TableRow* row : allRows)
	{

	}
}
