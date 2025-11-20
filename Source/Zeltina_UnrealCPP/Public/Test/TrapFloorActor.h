// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/ActionCharacter.h"
#include "TrapFloorActor.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTreadFloor);

UCLASS()
class ZELTINA_UNREALCPP_API ATrapFloorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrapFloorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Tread")
	void TreadTrap(AActor* Target);

public:	
	/*UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnTreadFloor OnTreadFloor;*/



protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Root = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UNiagaraComponent> Effect = nullptr;

private:
	TWeakObjectPtr<AActionCharacter> Player = nullptr;

};
