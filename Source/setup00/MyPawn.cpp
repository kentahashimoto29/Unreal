// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Player0（最小値）
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// 親子
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// カメラ
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));

	// 可視オブジェクト
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	// RootComponent
	OurCamera->SetupAttachment(RootComponent);

	// カメラ
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	// RootComponent
	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 移動量があればLocationを更新
	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}

	float CurrentScale = OurVisibleComponent->GetComponentScale().X;
	if (IsGroeing)
	{
		// 一秒間に倍のサイズに成長
		CurrentScale += DeltaTime;
	}

	else
	{
		// 拡大と同じ速度で半分に縮小
		CurrentScale -= (DeltaTime * 0.5f);
	}

	// スケール値を1.0～2.0の間で制御
	CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
	// 反映
	OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// MoveYの入力値をMove_YAxis関数へバインドする
	InputComponent->BindAxis("MoveY", this, &AMyPawn::Mode_YAxis);

	// MoveYの入力値をMove_YAxis関数へバインドする
	InputComponent->BindAxis("MoveX", this, &AMyPawn::Mode_XAxis);

	// Growの入力値をバインド
	InputComponent->BindAction("Grow", EInputEvent::IE_Pressed, this, &AMyPawn::StartGrowing);

	InputComponent->BindAction("Grow", EInputEvent::IE_Released, this, &AMyPawn::StopGrowing);
}

// Y方向の移動量を制御
void AMyPawn::Mode_YAxis(float AxisValue)
{
	//（一秒間に）
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * FloatSpeed;
}

// X方向の移動量を制御
void AMyPawn::Mode_XAxis(float AxisValue)
{
	//（一秒間に）
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * FloatSpeed;
}

// 成長スイッチ制御
void AMyPawn::StartGrowing()
{
	IsGroeing = true;
}

void AMyPawn::StopGrowing()
{
	IsGroeing = false;
}