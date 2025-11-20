// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/TrapFloorActor.h"
#include "NiagaraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

// Sets default values
ATrapFloorActor::ATrapFloorActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// Pawn만 Overlap
	Root->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Root->SetCollisionObjectType(ECC_WorldStatic);
	Root->SetCollisionResponseToAllChannels(ECR_Ignore);
	Root->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Root->SetGenerateOverlapEvents(true);

	// Overlap 이벤트 바인딩
	Root->OnComponentBeginOverlap.AddDynamic(this, &ATrapFloorActor::OnTrapBeginOverlap);

	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	Effect->SetupAttachment(Root);
	Effect->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

	// 처음엔 자동으로 재생되지 않게
	Effect->SetAutoActivate(false);

	// 디폴트 DamageType
	DamageTypeClass = UDamageType::StaticClass();
}

// Called when the game starts or when spawned
void ATrapFloorActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATrapFloorActor::OnTrapBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32                OtherBodyIndex,
	bool                 bFromSweep,
	const FHitResult& SweepResult
)
{
	if (bAlreadyTriggered)
	{
		return;
	}

	if (!OtherActor || OtherActor == this)
	{
		return;
	}

	// 플레이어만 반응하게
	AActionCharacter* OverlappedPlayer = Cast<AActionCharacter>(OtherActor);
	if (!OverlappedPlayer)
	{
		return;
	}

	Player = OverlappedPlayer;

	// 실제 트랩 발동
	TreadTrap(OtherActor);

	// 한 번만 발동하고 싶으면 true로
	bAlreadyTriggered = true;

	// 이후 더 이상 충돌 안 받게 하고 싶으면
	Root->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ATrapFloorActor::TreadTrap(AActor* Target)
{
	// 1) 나이아가라 이펙트 발동
	if (Effect)
	{
		Effect->Activate(true);   // Reset=true
	}

	// 2) 데미지 적용
	if (!Target)
	{
		return;
	}

	AController* InstigatorController = nullptr;

	// 플레이어 컨트롤러를 instigator로 설정
	if (AActionCharacter* ActionChar = Cast<AActionCharacter>(Target))
	{
		InstigatorController = ActionChar->GetController();
	}

	if (!DamageTypeClass)
	{
		DamageTypeClass = UDamageType::StaticClass();
	}

	UGameplayStatics::ApplyDamage(
		Target,                // 피해 받는 대상
		Damage,                // 데미지 값
		InstigatorController,  // instigator (없으면 nullptr)
		this,                  // 데미지를 준 액터 (트랩)
		DamageTypeClass        // 데미지 타입
	);
}

