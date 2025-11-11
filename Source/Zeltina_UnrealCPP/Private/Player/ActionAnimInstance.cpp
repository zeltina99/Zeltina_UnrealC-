// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActionAnimInstance.h"
#include "Player/ActionCharacter.h" 
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UActionAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	//APawn* ownerPawn = TryGetPawnOwner();
	//if (ownerPawn)
	//{
	//	OwnerMovementComponent = ownerPawn->GetMovementComponent();
	//}

	OwnerCharacter = Cast<AActionCharacter>(TryGetPawnOwner());

}

void UActionAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//TryGetPawnOwner()->GetVelocity().Size();	//	Tick이나 Update같이 빠르게 반복되는 곳에서는 불필요한 중복 실행은 방지해야한다.

	//if (OwnerMovementComponent.IsValid())
	//{
	//	const UPawnMovementComponent* movement = OwnerMovementComponent.Get();
	//	Speed = movement->Velocity.Size();
	// 
	//	Speed = OwnerMovementComponent.Get()->Velocity.Size();
	//}

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
