// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActionCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"

// Sets default values
AActionCharacter::AActionCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//USpringArmComponent* spring = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring"));
	//spring->SetupAttachment(RootComponent);

	//spring->TargetArmLength = 450.0f;
	//spring->bUsePawnControlRotation = true;

	//FRotator NewRotation(0, -30, 0);
	//spring->SetRelativeRotation(NewRotation);

	//UCameraComponent* CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	//CameraComp->SetupAttachment(spring);
	//CameraComp->bUsePawnControlRotation = false;

	//bUseControllerRotationYaw = false;
	//GetCharacterMovement()->bOrientRotationToMovement = true;
	////GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);

	//GetCharacterMovement()->MaxWalkSpeed = 500.0f;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 350.0f;
	SpringArm->SocketOffset = FVector(0, 0, 250);
	SpringArm->bUsePawnControlRotation = true;	// 스프링암의 회전을 컨트롤러에 맞춤

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(SpringArm);
	PlayerCamera->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));

	bUseControllerRotationYaw = false;	// 컨트롤러의 Yaw회전을 사용 안함

	GetCharacterMovement()->bOrientRotationToMovement = true;	// 이동 방향을 바라보게 회전
	GetCharacterMovement()->RotationRate = FRotator(0, 360, 0);
}

// Called when the game starts or when spawned
void AActionCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	AnimInstance = GetMesh()->GetAnimInstance();	// ABP 객체 가져오기

	// 게임 진행 중에 자주 변경되는 값은 시작 시점에서 리셋을 해주는 것이 좋다.
	CurrentStamina = MaxStamina;	// 시작할 때 최대치로 리셋
	bIsSprint = false;

}

// Called every frame
void AActionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//SetStamina(DeltaTime);
	LastStaminaUseTime += DeltaTime;
	if (LastStaminaUseTime > 3.0f)
	{
		CurrentStamina += 50 * DeltaTime;
	}

	if (bIsSprint)
	{
		CurrentStamina -= SprintStaminaCost * DeltaTime;
		LastStaminaUseTime = 0;
		if (CurrentStamina <= 0)
		{
			CurrentStamina = 0.0f;
			SetWalkMode();
		}
	}

}

// Called to bind functionality to input
void AActionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhanced = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (enhanced)	//	입력 컴포넌트가 향상된 입력 컴포넌트일 때
	{
		enhanced->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AActionCharacter::OnMoveInput);
		enhanced->BindActionValueLambda(IA_Sprint, ETriggerEvent::Started,
			[this](const FInputActionValue& _) {
				SetSprintMode();
			});
		enhanced->BindActionValueLambda(IA_Sprint, ETriggerEvent::Completed,
			[this](const FInputActionValue& _) {
				SetWalkMode();
			});
		/*enhanced->BindAction(IA_Sprint, ETriggerEvent::Started, this, &AActionCharacter::OnSprintStarted);
		enhanced->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &AActionCharacter::OnSprintEnded);
		enhanced->BindAction(IA_Sprint, ETriggerEvent::Canceled, this, &AActionCharacter::OnSprintEnded);*/
		enhanced->BindAction(IA_Attack, ETriggerEvent::Started, this, &AActionCharacter::OnAttackStarted);
		enhanced->BindAction(IA_Roll, ETriggerEvent::Triggered, this, &AActionCharacter::OnRollInput);
	}
}

void AActionCharacter::OnMoveInput(const FInputActionValue& InValue)
{
	FVector2D inputDirection = InValue.Get<FVector2D>();
	//UE_LOG(LogTemp, Log, TEXT("Dir : (%.1f, %.1f)"), inputDirection.X, inputDirection.Y);
	//UE_LOG(LogTemp, Log, TEXT("Dir : (%s)"), *inputDirection.ToString());

	/*FRotator ControlRot = Controller->GetControlRotation();
	FRotator YawRot(0.f, ControlRot.Yaw, 0.f);

	FVector ForwardDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	FVector RightDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDir, inputDirection.Y);
	AddMovementInput(RightDir, inputDirection.X);*/

	FVector moveDirection(inputDirection.Y, inputDirection.X, 0.0f);

	FQuat controlYawRotation = FQuat(FRotator(0, GetControlRotation().Yaw, 0));	//	컨트롤러의 Yaw회전을 따로 뽑아와서
	moveDirection = controlYawRotation.RotateVector(moveDirection);	//	이동 방향에 적용

	AddMovementInput(moveDirection);

}

//void AActionCharacter::OnSprintStarted(const FInputActionValue& InValue)
//{
//	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
//}
//
//void AActionCharacter::OnSprintEnded(const FInputActionValue& InValue)
//{
//	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
//}

void AActionCharacter::OnAttackStarted(const FInputActionValue& InValue)
{
	if (USkeletalMeshComponent* SkelMesh = GetMesh())
	{
		if (UAnimInstance* Anim = SkelMesh->GetAnimInstance())
		{
			if (!Anim->Montage_IsPlaying(AttackMontage))
			{
				Anim->Montage_Play(AttackMontage, 1.0f);
			}
		}
	}
}

void AActionCharacter::OnRollInput(const FInputActionValue& InValue)
{
	//if(Stamina > 5.0f)
	//{
		if (AnimInstance.IsValid())
		{
			if (!AnimInstance->IsAnyMontagePlaying() 
				&& CurrentStamina > RollStaminaCost)
			{
				if (!GetLastMovementInputVector().IsNearlyZero())	//	입력을 하는 중에만 즉시 회전
				{
					SetActorRotation(GetLastMovementInputVector().Rotation());	//	마지막 입력 방향으로 즉시 회전 시키기
				}
				CurrentStamina -= RollStaminaCost;
				LastStaminaUseTime = 0.0f;
				PlayAnimMontage(RollMontage);
				//Stamina -= 5.0f;
				//UE_LOG(LogTemp, Warning, TEXT("Stamina : %.1f"), Stamina);
			}
		}
	//}
}

void AActionCharacter::SetSprintMode()
{
	/*OnStamina = true;
	if(Stamina > 0)*/
	//{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	//}
		bIsSprint = true;
}

void AActionCharacter::SetWalkMode()
{
	/*OnStamina = false;*/
	//UE_LOG(LogTemp, Warning, TEXT("걷기 모드"));
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	bIsSprint = false;
}

//void AActionCharacter::SetStamina(float DeltaTime)
//{
//	//UE_LOG(LogTemp, Warning, TEXT("Stamina : %.1f"), Stamina);
//	if (OnStamina == true)
//	{
//		if(Stamina > 0)
//		{
//			Stamina -= DeltaTime;
//		}
//		else
//		{
//			SetWalkMode();
//		}
//		Delay = 0.0f;
//	}
//	else
//	{
//		Delay += DeltaTime;
//		if(Delay >= 3.0f && Stamina < 10.0f)
//		{
//			Stamina += DeltaTime;
//		}
//	}
//}


