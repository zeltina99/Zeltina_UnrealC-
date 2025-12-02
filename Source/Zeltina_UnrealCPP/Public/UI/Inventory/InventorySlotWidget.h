// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"

struct FInvenSlot;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnslotCliked, int32 InslotIndex);
/**
 * 
 */
UCLASS()
class ZELTINA_UNREALCPP_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 이 위젯이 보여줄 데이터를 세팅
	void InitializeSlot(int32 InIndex, FInvenSlot* InSlotData);

	// 설정된 데이터를 기반으로 위젯에서 표시하는 내용을 갱신
	void RefreshSlot() const;

protected:
	void ClearSlotWidget() const;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	FOnslotCliked OnSlotRightClick;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|InventorySlot", meta = (BindWidget))
	TObjectPtr<class UImage> ItemIconImage = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|InventorySlot", meta = (BindWidget))
	TObjectPtr<class UTextBlock> CountText = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|InventorySlot", meta = (BindWidget))
	TObjectPtr<class UTextBlock> SeparateText = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|InventorySlot", meta = (BindWidget))
	TObjectPtr<class UTextBlock> MaxCountText = nullptr;

private:
	int32 index = -1;

	FInvenSlot* SlotData = nullptr;

};
