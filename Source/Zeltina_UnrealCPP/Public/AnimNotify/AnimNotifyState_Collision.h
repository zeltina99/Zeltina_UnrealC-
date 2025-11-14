// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_Collision.generated.h"

/**
 * 
 */
UCLASS()
class ZELTINA_UNREALCPP_API UAnimNotifyState_Collision : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(
		USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		float TotalDuration,
		const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(
		USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY()
	TWeakObjectPtr<class AWeaponActor> Weapon = nullptr;


private:
	UPROPERTY()
	TWeakObjectPtr<class AActionCharacter> OwnerCharacter = nullptr;
	
};
