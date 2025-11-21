// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RangeAttackActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"

// Sets default values
ARangeAttackActor::ARangeAttackActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);

	RangeAttackCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RangeAttackCollision->SetupAttachment(root);
	RangeAttackCollision->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	RangeAttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RangeAttackEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	RangeAttackEffect->SetAutoActivate(false);
	RangeAttackEffect->SetupAttachment(RangeAttackCollision);

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

// Called when the game starts or when spawned
void ARangeAttackActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARangeAttackActor::RangeAttackEnable(bool bEnable)
{
	if (bEnable)
	{
		// 🔹 범위 공격 켤 때
		RangeAttackCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

		if (RangeAttackEffect)
		{
			RangeAttackEffect->Activate(true); // 처음부터 재생
		}

		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
	}
	else
	{
		// 🔹 범위 공격 끌 때
		RangeAttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		if (RangeAttackEffect)
		{
			RangeAttackEffect->Deactivate();
		}

		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}
}


