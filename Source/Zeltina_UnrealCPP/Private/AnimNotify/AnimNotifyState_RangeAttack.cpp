// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotifyState_RangeAttack.h"
#include "Player/ActionCharacter.h"

void UAnimNotifyState_RangeAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!OwnerCharacter.IsValid())
	{
		OwnerCharacter = Cast<AActionCharacter>(MeshComp->GetOwner());
	}
	if (OwnerCharacter.IsValid())
	{
		// 세번째 범위 공격 이펙트 켜기
		OwnerCharacter->OnRangeAttackEnable(true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UAnimNotifyState_RangeAttack::NotifyBegin : OwnerCharacter가 유효하지 않습니다."));
	}

}

void UAnimNotifyState_RangeAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{

	if (OwnerCharacter.IsValid())
	{
		// 세번째 범위 공격 이펙트 끄기
		OwnerCharacter->OnRangeAttackEnable(false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UAnimNotifyState_RangeAttack::NotifyBegin : OwnerCharacter가 유효하지 않습니다."));
	}
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
