// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttackPowerChanged, float, Weapon, float, Attack);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZELTINA_UNREALCPP_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	inline float GetAttackPower() const { return AttackPower; }

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnAttackPowerChanged OnAttackPowerChanged;

private:
	inline void SetAttackPower(float InValue) {
		WeaponPower = InValue;
		OnAttackPowerChanged.Broadcast(WeaponPower, AttackPower);
	};

protected:
	// 플레이어 공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Attack")
	float AttackPower = 15.0f;

	// 무기 공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Attack")
	float WeaponPower = 0.0f;
		
};
