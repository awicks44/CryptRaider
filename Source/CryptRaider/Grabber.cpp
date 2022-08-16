// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

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
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent * PhysicsHandle = GetPhysicsHandle();
	
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("No Physics Handle pointer"));
		return;
	}

	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

void UGrabber::Release()
{
	UPhysicsHandleComponent * PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{	
		return;
	}
	
	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
	}
	
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent * PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{	
		return;
	}

	FHitResult HitResult;
	
	bool HasHit = GetGrabbleInReach(HitResult);

	if (HasHit)
	{
		UPrimitiveComponent * HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, false, 5);
		PhysicsHandle->GrabComponentAtLocationWithRotation(
		HitComponent,
		NAME_None,
		HitResult.ImpactPoint,
		GetComponentRotation()
		);
	}
	
}

UPhysicsHandleComponent * UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent * Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	
	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysics Component"));
	}
	return Result;
}

bool UGrabber::GetGrabbleInReach(FHitResult & OutHitResult)
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false);		
	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Emerald, false, 5);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);	
	
	return GetWorld()->SweepSingleByChannel(
		OutHitResult, 
		Start, End, 
		FQuat::Identity, 
		ECC_GameTraceChannel2,
		Sphere
	);
}