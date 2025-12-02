// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemDataAsset.h"
#include "Data/UsableItem.h"
#include "UsableItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class ZELTINA_UNREALCPP_API UUsableItemDataAsset : public UItemDataAsset, public IUsableItem
{
	GENERATED_BODY()
	
};
