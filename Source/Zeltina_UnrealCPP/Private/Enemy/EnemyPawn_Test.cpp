// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPawn_Test.h"
#include "Enemy/DamagePopupActor.h"
#include "Framework/DamagePopupSubsystem.h"

// Sets default values
AEnemyPawn_Test::AEnemyPawn_Test()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

    PopupLocation = CreateDefaultSubobject<USceneComponent>(TEXT("PopupLocation"));
    PopupLocation->SetupAttachment(Mesh);
    PopupLocation->SetRelativeLocation(FVector(0, 0, 100));
}

// Called when the game starts or when spawned
void AEnemyPawn_Test::BeginPlay()
{
	Super::BeginPlay();
    OnTakeAnyDamage.AddDynamic(this, &AEnemyPawn_Test::OnTakeDamage);
}


// Called to bind functionality to input
void AEnemyPawn_Test::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyPawn_Test::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    //GEngine->AddOnScreenDebugMessage()
    UE_LOG(LogTemp, Log, TEXT("Damage : %.1f"), Damage);

    /*ADamagePopupActor* actor = GetWorld()->SpawnActor<ADamagePopupActor>(
        DamagePopupClass, PopupLocation->GetComponentToWorld());
    if (actor)
    {
        actor->PopupActivate(Damage);
    }*/

    UDamagePopupSubsystem* popupSystem = GetWorld()->GetSubsystem<UDamagePopupSubsystem>();
    popupSystem->ShowDamagePopup(Damage, PopupLocation->GetComponentLocation());

}



