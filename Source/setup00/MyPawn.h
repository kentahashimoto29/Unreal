// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class SETUP00_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	// �\������
	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingProperty")
	float FloatSpeed = 300.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Y�����̈ړ��ʂ𐧌�
	void Mode_YAxis(float AxisValue);
	// X�����̈ړ��ʂ𐧌�
	void Mode_XAxis(float AxisValue);

	// ���݂̑��x
	FVector CurrentVelocity;

	// �����X�C�b�`����
	void StartGrowing();
	void StopGrowing();

	// �����t���O
	bool IsGroeing;
};
