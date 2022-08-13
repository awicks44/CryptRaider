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

	float Damage = 0;
	float & DamageRef = Damage;	
	DamageRef = 5;

	// to variables that point to the same pice of memory
	UE_LOG(LogTemp, Display, TEXT("DamageRef: %f, Damage: %f"), DamageRef, Damage);	
	PrintDamage(Damage);
	UE_LOG(LogTemp, Display, TEXT("DamageRef: %f, Damage: %f"), DamageRef, Damage);
	
}

// with this call, we aren't actually making a copy of damage inside the method
// we are getting a reference of the damage var calling this function. We are accessing
// the original piece of memory
void UGrabber::PrintDamage(float& Damage)
{
	Damage = 2;
	UE_LOG(LogTemp, Display, TEXT("The Damage: %f"), Damage);
}


