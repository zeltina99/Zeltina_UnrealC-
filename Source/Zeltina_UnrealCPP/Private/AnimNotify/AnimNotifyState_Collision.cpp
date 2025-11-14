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
        if (!Weapon.IsValid())  // 무기가 없다면
        {
            TArray<AActor*> AttachedActors; // 캐릭터에 붙어 있는 액터들을 담을 배열
            OwnerCharacter->GetAttachedActors(AttachedActors);  // 현재 Attach된 모든 액터들을 배열에 채워 넣기

            for (AActor* Actor : AttachedActors)    // 배열에 있는 액터들을 하나씩 검사
            {
                if (AWeaponActor* FoundWeapon = Cast<AWeaponActor>(Actor))  // 액터가 WeaponActor타입이면 캐스팅 성공
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
