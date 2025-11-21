// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotify_CameraShake.h"
#include "Player/ActionCharacter.h"

void UAnimNotify_CameraShake::Notify(
	USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!OwnerCharacter.IsValid())
	{
		OwnerCharacter = Cast<AActionCharacter>(MeshComp->GetOwner());
	}

	if (OwnerCharacter.IsValid())
	{
		OwnerCharacter->OnCameraShakeEnable();//의 카메라를 흔드는 함수를 호출
	}

}
