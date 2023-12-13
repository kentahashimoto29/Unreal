// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawnMovementComponent.h"


void UMyPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 移動可能になっているかチェック
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		// 移動ベクトルを取得
		FVector DesiredMovementThisFrame =
			ConsumeInputVector().GetClampedToMaxSize(1.0f)* DeltaTime * 150.0f;

		if (!DesiredMovementThisFrame.IsNearlyZero())
		{
			FHitResult Hit;
			SafeMoveUpdatedComponent(DesiredMovementThisFrame,
				UpdatedComponent->GetComponentRotation(),
				true,
				Hit);

			// 当たり判定が起きたら滑らかに移動
				if (Hit.IsValidBlockingHit())
				{
					SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
				}
		}

		return;
	}
}