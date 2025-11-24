// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "EnemyCountSubsystem.generated.h"

class AEnemyPawn_Test;


// 적 수가 변했을 때 (변경 후 수를 같이 보냄)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyCountChanged, int32, NewCount);

// 적이 모두 사라졌을 때 (NewCount == 0)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllEnemiesDefeated);

/**
 * 
 */
UCLASS()
class ZELTINA_UNREALCPP_API UEnemyCountSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UEnemyCountSubsystem();

	// 적 등록 (BeginPlay에서 호출)
	void RegisterEnemy(AEnemyPawn_Test* InEnemy);

	// 적 해제 (EndPlay / 죽을 때 Destroy 직전에 호출)
	void UnregisterEnemy(AEnemyPawn_Test* InEnemy);

	// 현재 적 수 얻기 (BP에서도 사용 가능)
	UFUNCTION(BlueprintCallable, Category = "Enemy Count")
	int32 GetEnemyCount() const { return EnemyCount; }

	// 적 수가 변할 때마다 브로드캐스트
	UPROPERTY(BlueprintAssignable, Category = "Enemy Count")
	FOnEnemyCountChanged OnEnemyCountChanged;

	// 적이 0이 되었을 때 한 번 브로드캐스트
	UPROPERTY(BlueprintAssignable, Category = "Enemy Count")
	FOnAllEnemiesDefeated OnAllEnemiesDefeated;

protected:
	virtual void Deinitialize() override;

private:
	// 현재 월드에 살아 있는 적 목록
	UPROPERTY()
	TSet<TObjectPtr<AEnemyPawn_Test>> Enemies;

	// 현재 적 수 (Enemies.Num() 캐싱)
	UPROPERTY()
	int32 EnemyCount = 0;

	void BroadcastCountChanged();

};
