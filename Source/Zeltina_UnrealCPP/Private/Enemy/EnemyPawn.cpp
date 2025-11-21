// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPawn.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetCollisionProfileName(TEXT("Pawn"));

	CurrentHealth = MaxHealth;
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

//// Called every frame
//void AEnemyPawn::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemyPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (DamageAmount <= 0.0f)
	{
		return 0.0f;
	}

	CurrentHealth -= DamageAmount;
	CurrentHealth = FMath::Max(CurrentHealth, 0.f);

	UE_LOG(LogTemp, Log, TEXT("[EnemyPawn] 받은 데미지 =%.1f, 남은 현재 HP=%.1f"), DamageAmount, CurrentHealth);

	return 0.0f;
}

