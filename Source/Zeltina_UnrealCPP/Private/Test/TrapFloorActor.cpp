// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/TrapFloorActor.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATrapFloorActor::ATrapFloorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Root->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	Effect->SetupAttachment(Root);
	Effect->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

}

// Called when the game starts or when spawned
void ATrapFloorActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATrapFloorActor::TreadTrap(AActor* Target)
{
	// Effect가 터지고 데미지가 들어감
	// AController* instigator = nullptr;
	// UGameplayStatics::ApplyDamage(OtherActor, finalDamage, instigator, this, DamageType);




}

