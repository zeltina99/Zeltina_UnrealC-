// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryCloseRequested);

/**
 * 
 */


UCLASS()
class ZELTINA_UNREALCPP_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void InitializeInventoryWidget(class UInventoryComponent* InventoryComponent);
	void ClearInventoryWidget();

	UPROPERTY(BlueprintAssignable, Category = "UI|Inventory")
	FOnInventoryCloseRequested OnInventoryCloseRequested;
	
private:
	UFUNCTION()
	void OnCloseClicked();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> CloseButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUniformGridPanel> SlotGridPanel = nullptr;

private:
	UPROPERTY()
	TWeakObjectPtr<UInventoryComponent> TargetInventory = nullptr;
};
