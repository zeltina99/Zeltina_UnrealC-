// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/ActionCharacter.h"
#include "TrapFloorActor.generated.h"

class UStaticMeshComponent;
class UNiagaraComponent;
class UPrimitiveComponent;
class UDamageType;

UCLASS()
class ZELTINA_UNREALCPP_API ATrapFloorActor : public AActor
{
	GENERATED_BODY()

public:
	ATrapFloorActor();

protected:
	virtual void BeginPlay() override;

	// 발판을 밟았을 때 실제로 트랩을 발동시키는 함수
	UFUNCTION(BlueprintCallable, Category = "Trap")
	void TreadTrap(AActor* Target);

	// Overlap 이벤트 콜백
	UFUNCTION()
	void OnTrapBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32                OtherBodyIndex,
		bool                 bFromSweep,
		const FHitResult& SweepResult
	);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Root = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UNiagaraComponent> Effect = nullptr;

	// 한 번 밟히면 다시는 발동 안 되게 하고 싶을 때 사용
	UPROPERTY(VisibleAnywhere, Category = "Trap")
	bool bAlreadyTriggered = false;

	// 들어갈 데미지량
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trap")
	float Damage = 50.f;

	// 데미지 타입
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trap")
	TSubclassOf<UDamageType> DamageTypeClass;

private:
	TWeakObjectPtr<AActionCharacter> Player = nullptr;
};
