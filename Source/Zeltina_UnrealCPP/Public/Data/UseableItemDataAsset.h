// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UseableItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class ZELTINA_UNREALCPP_API UUseableItemDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void UseItem(AActor* InTarget);

};
