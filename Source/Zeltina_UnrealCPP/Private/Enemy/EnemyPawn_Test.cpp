// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPawn_Test.h"

// Sets default values
AEnemyPawn_Test::AEnemyPawn_Test()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyPawn_Test::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyPawn_Test::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyPawn_Test::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

