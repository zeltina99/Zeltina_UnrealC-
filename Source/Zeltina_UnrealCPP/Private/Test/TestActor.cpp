// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/TestActor.h"

// Sets default values
ATestActor::ATestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	// Super = 부모 클래스
	Super::BeginPlay(); // 부모 클래스의 BeginPlay를 실행해라.

	UE_LOG(LogTemp, Log, TEXT("Hello Unreal. 한글도 됨. 일반 로그."));
	UE_LOG(LogTemp, Warning, TEXT("Hello Unreal. 한글도 됨. 경고 로그."));
	UE_LOG(LogTemp, Error, TEXT("Hello Unreal. 한글도 됨. 에러 로그."));

}

void ATestActor::Test_NormalFunction()
{
	UE_LOG(LogTemp, Log, TEXT("Test_NormalFunction 호출"));
}

void ATestActor::Test_UFunction()
{
	UE_LOG(LogTemp, Log, TEXT("Test_Function 호출"));
}

// Test_NativeEventFunction의 구현은 Implementation를 붙여야 한다.
void ATestActor::Test_NativeEventFunction_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Test_NativeEventFunction 호출"));
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Test_NativeEventFunction(); C++에서 호출은 _Implementation안붙인 이름 사용

}

/*
	언리얼 C++ 개요
	 - 언리얼 C++와 블루프린트의 관계
	  - 서로 계층이 다르다. (언리얼 엔진 -> C++ class -> Blueprint)
	  -> C++는 블루프린트의 내용을 알 수 없다.
	  -> 블루프린트는 C++의 내용을 허가 정도에 따라 알 수 있다.

	언리얼 데이터 타입
	 - 언리얼은 C++의 표준 라이브러리를 사용하지 않는다.
	 - 자체적으로 대부분의 타입과 라이브러리를 구현.
	 - int -> int32

	문자열 타입
	 - FString : 일반 문자열(std::string과 유사)
	 - FName : 이름 붙이기 용도. 빠른 비교와 메모리 절약을 위한 불변 문자열. 대소문자 구분 없음.
	 - FText : 현지화 지원 문자열.

	컬렉션 타입(데이터 컨테이너, 템플릿 기반)
	 - TArray : std::vector와 같은 컬렉션. 블루프린트 완전 지원
	 - TMap : std::unordered_map과 같은 컬렉션. 키-값 맵. 순서 보장 안됨. 블루프린트 일부 지원.
	 - TSet : std::unordered_set과 같은 컬렉션. 유니크한 목록 저장용. 블루프린트 일부 지원

	트랜스폼 및 수학 타입
	 - FVector : 위치, 방향, 벡터
	 - FRotator : 회전(오일러 각도)
	 - FQuat : 회전(쿼터니언)
	 - FTransform : 위치, 회전, 스케일 모두 저장
	 - FMath 라이브러리 : 다양한 수학용 정적 함수 제공

	스마트 포인터
	 - 할당한 메모리가 더 이상 사용되지 않을 때 자동으로 해제해주는 포인터
	 - 일반 클래스용
	  - TSharedPtr, TWeakPtr, TUniquePtr
	 - UObject용
	  - TObjectPtr, TWeakObjectPtr, TSoftObjectPtr, TSubclassOf, TSoftClassPtr

	언리얼 핵심 클래스
	 - UObject
	  - 모든 언리얼 오브젝트의 최상위 부모 클래스
	  - 가비지 컬랙션으로 메모리 관리
	  - 모든 자식 클래스는 이름에 U를 접두사로 붙인다.(자동으로 붙음)
	  - 레벨에 직접적으로 존재하지 않고 데이터 관리나 로직에 사용됨
	 - AActor
	  - 레벨 내에 직접적으로 존재하고 Transform(위치, 회전, 스케일)을 가진다.
	  - AActor의 자식클래스는 A를 접두사로 붙인다.(자동으로 붙음)
	  - AActor는 여러 UActorComponent를 포함시켜 다양한 기능을 확장할 수 있다.
	 - UActorComponent
	  - AActor에 부착되어 기능을 확장
	  - 단독으로 월드에 존재할 수 없다. 반드시 액터에 부착되어야 한다.
	  - 자식클래스는 U를 접두사로 가진다.
	  - 자체 Tick함수가 존재한다.

	반드시 C++로 구현해야 할 요소들
	 - 구조체, enum, 인터페이스
	 - 블루프린트로 만들어진것은 C++에서 확인이 불가능하기 때문에

*/
