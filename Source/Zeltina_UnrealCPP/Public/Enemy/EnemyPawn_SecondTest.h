// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyPawn_Test.h"
#include "EnemyPawn_SecondTest.generated.h"

/**
 * 
 */
UCLASS()
class ZELTINA_UNREALCPP_API AEnemyPawn_SecondTest : public AEnemyPawn_Test
{
	GENERATED_BODY()

public:
    AEnemyPawn_SecondTest();

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    // 필요하다면 이쪽에서 체력/데미지 처리도 커스텀
    virtual float TakeDamage(
        float DamageAmount,
        FDamageEvent const& DamageEvent,
        AController* EventInstigator,
        AActor* DamageCauser
    ) override;

protected:
    // 예시: 체력 추가하고 싶으면 이런 식으로
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy|Stat")
    float MaxHP = 100.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|Stat")
    float CurrentHP = 0.f;
};
