// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPawn_SecondTest.h"
#include "Framework/EnemyCountSubsystem.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

AEnemyPawn_SecondTest::AEnemyPawn_SecondTest()
{
}

void AEnemyPawn_SecondTest::BeginPlay()
{
    Super::BeginPlay();

    CurrentHP = MaxHP;

    if (UWorld* World = GetWorld())
    {
        if (UEnemyCountSubsystem* EnemySubsystem = World->GetSubsystem<UEnemyCountSubsystem>())
        {
            EnemySubsystem->RegisterEnemy(this);
        }
    }
}

void AEnemyPawn_SecondTest::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (UWorld* World = GetWorld())
    {
        if (UEnemyCountSubsystem* EnemySubsystem = World->GetSubsystem<UEnemyCountSubsystem>())
        {
            EnemySubsystem->UnregisterEnemy(this);
        }
    }

    Super::EndPlay(EndPlayReason);
}

float AEnemyPawn_SecondTest::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    const float ActualDamage =
        Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    // 체력 감소 로직 (원하면)
    CurrentHP -= ActualDamage;

    // 죽으면 Destroy → EndPlay → 서브시스템에서 자동 Unregister
    if (CurrentHP <= 0.f)
    {
        Destroy();
    }

    return ActualDamage;
}
