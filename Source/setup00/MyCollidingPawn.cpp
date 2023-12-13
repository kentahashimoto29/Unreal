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

	// RootComponent�𓖂��蔻��p��ShereComponent�ɐݒ肷��
	USphereComponent* SphereComponent =
		CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));

	RootComponent = SphereComponent;

	// ���a�̐ݒ�
	SphereComponent->InitSphereRadius(40.0f);

	// �R���W�����v���t�@�C���̐ݒ�
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	// VisualMesh�̐ݒ�
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

		// �X�v�����O�A�[���ɂ��J�����̐ݒ�
		USpringArmComponent* SpringArm =
		CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachimentArm"));
		SpringArm->SetupAttachment(RootComponent);
		SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
		SpringArm->TargetArmLength = 400.0f;
		SpringArm->bEnableCameraLag = true;
		SpringArm->CameraLagSpeed = 3.0f;

		// �J�����𐶐����A�X�v�����O�A�[���ɐe�q�t��
		UCameraComponent* Camera =
			CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));

		Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

		// ���̓v���C���[�̐ݒ�
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

	// �ړ��ʂ������Location���X�V
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

	// MoveY�̓��͒l��Move_YAxis�֐��փo�C���h����
	InputComponent->BindAxis("MoveY", this, &AMyCollidingPawn::Mode_YAxis);

	// MoveY�̓��͒l��Move_YAxis�֐��փo�C���h����
	InputComponent->BindAxis("MoveX", this, &AMyCollidingPawn::Mode_XAxis);

}


// Y�����̈ړ��ʂ𐧌�
void AMyCollidingPawn::Mode_YAxis(float AxisValue)
{
	//�i��b�ԂɁj
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * FloatSpeed;
}

// X�����̈ړ��ʂ𐧌�
void AMyCollidingPawn::Mode_XAxis(float AxisValue)
{
	//�i��b�ԂɁj
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * FloatSpeed;
}
