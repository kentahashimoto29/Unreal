// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���b�V���̍쐬
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	// �A�Z�b�g�̐ݒ�
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	// �쐬�ɐ�������������
	if (CubeVisualAsset.Succeeded())
	{
		// �p�����[�^�ݒ�
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsFloat == true)
	{
		// �A�N�^�̈ʒu���擾
		FVector NewLocation = GetActorLocation();

		// ���݂̍������Z�o
		float RunningTime = GetGameTimeSinceCreation();
		float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));

		// Z(����)��ݒ�
		NewLocation.Z += DeltaHeight * FloatSpeed;		// scale20

		// �A�N�^�̈ʒu�֐ݒ�
		SetActorLocation(NewLocation);
	}
}

