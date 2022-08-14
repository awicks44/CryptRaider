// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("Grabber Begin Play"));

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false);

	float Damage;
	if (HasDamage(Damage))
	{
		PrintDamage(Damage);
	}

}

// with this call, we aren't actually making a copy of damage inside the method
// we are getting a reference of the damage var calling this function. We are accessing
// the original piece of memory. We can accidentally modify variables unexpected. To fix that
// we can put const in front of the data type reference declaration. It tells C++ that we can only
// utilize the variable and not modify. 
void UGrabber::PrintDamage(const float& Damage)
{
	//Damage = 2;
	UE_LOG(LogTemp, Display, TEXT("The Damage: %f"), Damage);
}

// this is how we use non-const rewferences as out parameters. A way of getting multiple 
// rewturn values out of a function
bool UGrabber::HasDamage(float& OutDamage)
{
	OutDamage = 5;
	return true;
}


