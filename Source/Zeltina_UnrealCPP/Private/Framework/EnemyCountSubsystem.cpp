// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/EnemyCountSubsystem.h"

void UEnemyCountSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentEnemyCount = 0;	// 혹시나 싶어서 넣은 코드(없어도 상관없음)
	UE_LOG(LogTemp, Log, TEXT("UEnemyTrackingSubsystem::Initialize"));
}

void UEnemyCountSubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Log, TEXT("UEnemyTrackingSubsystem::Deinitialize"));
	Super::Deinitialize();
}

void UEnemyCountSubsystem::RegistEnemy()
{
	CurrentEnemyCount++;
	OnEnemyCountChanged.Broadcast(CurrentEnemyCount);
}

void UEnemyCountSubsystem::UnregistEnemy()
{
	if (CurrentEnemyCount > 0)
	{
		CurrentEnemyCount--;
		OnEnemyCountChanged.Broadcast(CurrentEnemyCount);

		if (CurrentEnemyCount <= 0)
		{
			OnAllEnemyClear.Broadcast();
		}
	}
}
