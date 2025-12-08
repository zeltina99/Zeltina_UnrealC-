// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidget.generated.h"

/**
 * 
 */
UCLASS()
class ZELTINA_UNREALCPP_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void InitializeShop(UDataTable* ItemList);

	void AddToItemSellDelegate(const FScriptDelegate& Delegate);

	UFUNCTION()
	void UpdateAllBuyButtonState(int32 _);

protected:
	void ResetShopItemListWidget();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Shop|Sell", meta = (BindWidget))
	TObjectPtr<class UShopItemSellWidget> ItemSellWidget = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|Buy", meta = (BindWidget))
	TObjectPtr<class UShopItemListWidget> ItemListWidget = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Shop", meta = (BindWidget))
	TObjectPtr<class UButton> Exit = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop|Buy")
	TWeakObjectPtr<UDataTable> ShopItemList = nullptr;

};
