// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/EnemyCountSubsystem.h"

UEnemyCountSubsystem::UEnemyCountSubsystem()
{
}

void UEnemyCountSubsystem::RegisterEnemy(AEnemyPawn_Test* InEnemy)
{
	if (InEnemy == nullptr)
	{
		return;
	}

	// 이미 등록된 적이면 무시
	if (Enemies.Contains(InEnemy))
	{
		return;
	}

	Enemies.Add(InEnemy);
	EnemyCount = Enemies.Num();

	BroadcastCountChanged();
}

void UEnemyCountSubsystem::UnregisterEnemy(AEnemyPawn_Test* InEnemy)
{
	if (!InEnemy)
	{
		return;
	}

	if (Enemies.Remove(InEnemy) > 0)
	{
		EnemyCount = Enemies.Num();

		BroadcastCountChanged();

		// 모두 사라졌으면 AllEnemiesDefeated 브로드캐스트
		if (EnemyCount == 0)
		{
			OnAllEnemiesDefeated.Broadcast();
		}
	}
}

void UEnemyCountSubsystem::Deinitialize()
{
	Enemies.Empty();
	EnemyCount = 0;

	Super::Deinitialize();
}

void UEnemyCountSubsystem::BroadcastCountChanged()
{
	OnEnemyCountChanged.Broadcast(EnemyCount);
}
