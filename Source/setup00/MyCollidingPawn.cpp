// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCollidingPawn.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyCollidingPawn::AMyCollidingPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// RootComponentを当たり判定用のShereComponentに設定する
	USphereComponent* SphereComponent =
		CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));

	RootComponent = SphereComponent;

	// 半径の設定
	SphereComponent->InitSphereRadius(40.0f);

	// コリジョンプロファイルの設定
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	// VisualMeshの設定
	UStaticMeshComponent* SphereVisual =
		CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));

	SphereVisual->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));

	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));

		// スプリングアームによるカメラの設定
		USpringArmComponent* SpringArm =
		CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachimentArm"));
		SpringArm->SetupAttachment(RootComponent);
		SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
		SpringArm->TargetArmLength = 400.0f;
		SpringArm->bEnableCameraLag = true;
		SpringArm->CameraLagSpeed = 3.0f;

		// カメラを生成し、スプリングアームに親子付け
		UCameraComponent* Camera =
			CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));

		Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

		// 入力プレイヤーの設定
		AutoPossessPlayer = EAutoReceiveInput::Player0;
	}
}

// Called when the game starts or when spawned
void AMyCollidingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCollidingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 移動量があればLocationを更新
	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void AMyCollidingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// MoveYの入力値をMove_YAxis関数へバインドする
	InputComponent->BindAxis("MoveY", this, &AMyCollidingPawn::Mode_YAxis);

	// MoveYの入力値をMove_YAxis関数へバインドする
	InputComponent->BindAxis("MoveX", this, &AMyCollidingPawn::Mode_XAxis);

}


// Y方向の移動量を制御
void AMyCollidingPawn::Mode_YAxis(float AxisValue)
{
	//（一秒間に）
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * FloatSpeed;
}

// X方向の移動量を制御
void AMyCollidingPawn::Mode_XAxis(float AxisValue)
{
	//（一秒間に）
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * FloatSpeed;
}
