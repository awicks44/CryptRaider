// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector TargetLocation = OriginalLocation;
	
	if (ShouldMove)
	{
		// if we should move then add the moveOffset to the target location because that's how far we want to 
		// go. If we shuln't move then the targetLocation will just be the start location. 
		// this allows for going back and forth
		TargetLocation = OriginalLocation + MoveOffset;
	}

	FVector CurrentLocation = GetOwner()->GetActorLocation();	
	float Speed = MoveOffset.Length() / MoveTime;
	
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);

	(*GetOwner()).SetActorLocation(NewLocation);
}

void UMover::SetShouldMove(bool InjectShouldMove)
{
	ShouldMove = InjectShouldMove;
}

