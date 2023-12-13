// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawnMovementComponent.h"
#include "MyCollidingPawn.generated.h"

UCLASS()
class SETUP00_API AMyCollidingPawn : public APawn
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere)
		UMyPawnMovementComponent* OurMovementComponent;

		float FloatSpeed = 300.0f;


public:
	// Sets default values for this pawn's properties
	AMyCollidingPawn();

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

	void MoveForward(float AxisValue);

	// ���݂̑��x
	FVector CurrentVelocity;

	virtual UMyPawnMovementComponent* AMyCollidingPawn::GetMovementComponent() const override;


};
