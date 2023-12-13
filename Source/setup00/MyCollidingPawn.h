// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyCollidingPawn.generated.h"

UCLASS()
class SETUP00_API AMyCollidingPawn : public APawn
{
	GENERATED_BODY()


		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingProperty")
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

	// Y•ûŒü‚ÌˆÚ“®—Ê‚ğ§Œä
	void Mode_YAxis(float AxisValue);
	// X•ûŒü‚ÌˆÚ“®—Ê‚ğ§Œä
	void Mode_XAxis(float AxisValue);

	// Œ»İ‚Ì‘¬“x
	FVector CurrentVelocity;

};
