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

	// ... testing xzfsdsad  s 
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor * Owner = GetOwner();
	//*Owner --> gets us to the actor itself
	//(*Owner). --> GetNameOrLabel
	//Owner->GetNameOrLabel

	// float MyFloat = 5;
	// float* YourFloat = &MyFloat;	

	// UE_LOG(LogTemp, Warning, TEXT("YourFloat Value: %f"), *YourFloat);

	FVector Location = Owner->GetActorLocation();	

	UE_LOG(LogTemp, Display, TEXT("Mover Owner Address: %s"), *(*Owner).GetActorNameOrLabel());
	UE_LOG(LogTemp, Display, TEXT("The Location is %s"), *Location.ToCompactString());

	// ...
	
}

