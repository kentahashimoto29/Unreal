// Fill out your copyright notice in the Description page of Project Settings.


#include "My_Pawn.h"

// Sets default values
AMy_Pawn::AMy_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMy_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMy_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMy_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

