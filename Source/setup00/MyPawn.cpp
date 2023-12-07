// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Player0�i�ŏ��l�j
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// �e�q
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// �J����
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));

	// ���I�u�W�F�N�g
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	// RootComponent
	OurCamera->SetupAttachment(RootComponent);

	// �J����
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

	// �ړ��ʂ������Location���X�V
	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}

	float CurrentScale = OurVisibleComponent->GetComponentScale().X;
	if (IsGroeing)
	{
		// ��b�Ԃɔ{�̃T�C�Y�ɐ���
		CurrentScale += DeltaTime;
	}

	else
	{
		// �g��Ɠ������x�Ŕ����ɏk��
		CurrentScale -= (DeltaTime * 0.5f);
	}

	// �X�P�[���l��1.0�`2.0�̊ԂŐ���
	CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
	// ���f
	OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// MoveY�̓��͒l��Move_YAxis�֐��փo�C���h����
	InputComponent->BindAxis("MoveY", this, &AMyPawn::Mode_YAxis);

	// MoveY�̓��͒l��Move_YAxis�֐��փo�C���h����
	InputComponent->BindAxis("MoveX", this, &AMyPawn::Mode_XAxis);

	// Grow�̓��͒l���o�C���h
	InputComponent->BindAction("Grow", EInputEvent::IE_Pressed, this, &AMyPawn::StartGrowing);

	InputComponent->BindAction("Grow", EInputEvent::IE_Released, this, &AMyPawn::StopGrowing);
}

// Y�����̈ړ��ʂ𐧌�
void AMyPawn::Mode_YAxis(float AxisValue)
{
	//�i��b�ԂɁj
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * FloatSpeed;
}

// X�����̈ړ��ʂ𐧌�
void AMyPawn::Mode_XAxis(float AxisValue)
{
	//�i��b�ԂɁj
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * FloatSpeed;
}

// �����X�C�b�`����
void AMyPawn::StartGrowing()
{
	IsGroeing = true;
}

void AMyPawn::StopGrowing()
{
	IsGroeing = false;
}