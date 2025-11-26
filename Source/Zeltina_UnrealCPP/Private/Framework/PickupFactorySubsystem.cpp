// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/PickupFactorySubsystem.h"

void UPickupFactorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Initialize(Collection);

	LoadPickupClassesMap();
}

APickup* UPickupFactorySubsystem::SpawnPickup(EItemCode InCode, FVector InLocation, FRotator InRotatr)
{
	return nullptr;
}

void UPickupFactorySubsystem::LoadPickupClassesMap()
{
}
