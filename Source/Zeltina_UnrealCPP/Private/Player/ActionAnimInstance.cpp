// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActionAnimInstance.h"
#include "Player/ActionCharacter.h" 
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UActionAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	OwnerCharacter = Cast<AActionCharacter>(TryGetPawnOwner());

}

void UActionAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!OwnerCharacter)
	{
		OwnerCharacter = Cast<AActionCharacter>(TryGetPawnOwner());
	}
	if (!OwnerCharacter)
	{
		return;
	}

	const FVector V = OwnerCharacter->GetVelocity();
	Speed = FVector(V.X, V.Y, 0.f).Size();

}
