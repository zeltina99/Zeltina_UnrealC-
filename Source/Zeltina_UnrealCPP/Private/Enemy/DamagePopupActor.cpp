// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/DamagePopupActor.h"

// Sets default values
ADamagePopupActor::ADamagePopupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADamagePopupActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamagePopupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

