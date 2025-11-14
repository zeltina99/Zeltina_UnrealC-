// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotifyState_Collision.h"
#include "Player/ActionCharacter.h"
#include "Weapon/WeaponActor.h"

void UAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
    OwnerCharacter = Cast<AActionCharacter>(MeshComp->GetOwner());
    if (OwnerCharacter.IsValid())
    {
        if (!Weapon.IsValid())
        {
            TArray<AActor*> AttachedActors;
            OwnerCharacter->GetAttachedActors(AttachedActors);

            for (AActor* Actor : AttachedActors)
            {
                if (AWeaponActor* FoundWeapon = Cast<AWeaponActor>(Actor))
                {
                    Weapon = FoundWeapon;
                    break;
                }
            }
        }
        if (Weapon.IsValid())
        {
            Weapon->AttackEnable(true);   // 공격 구간 시작: 충돌 켜기
        }
    }
}

void UAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    if (Weapon.IsValid())
    {
        Weapon->AttackEnable(false);      // 공격 구간 끝: 충돌 끄기
    }

	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
