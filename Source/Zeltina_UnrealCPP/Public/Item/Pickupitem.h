// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Pickup.h"
#include "Pickupitem.generated.h"

/**
 * 
 */
UCLASS()
class ZELTINA_UNREALCPP_API APickupitem : public APickup
{
	GENERATED_BODY()
	
public:
	virtual void OnPickupComplete_Implementation() override;

	inline void SetItemCount(int32 InCount) { ItemCount = InCount; }

protected:
	// 이 픽업을 먹었을 때 얻을 아이템
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Item")
	TObjectPtr<class UItemDataAsset> PickItemData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Item")
	int32 ItemCount = 1;
};
