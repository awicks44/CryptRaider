// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"
#include "Mover.h"

UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();
    
    UE_LOG(LogTemp, Warning, TEXT("Trigger Component Begin Play"));
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor *GoodActor = GetAcceptableActor();

    if (GoodActor != nullptr)
    {
        UPrimitiveComponent * Component = Cast<UPrimitiveComponent>(GoodActor->GetRootComponent());
        if (Component != nullptr)
        {
            
            Component->SetSimulatePhysics(false);
        }
        
        GoodActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
        Mover->SetShouldMove(true);
        
    }
    else 
    {
        Mover->SetShouldMove(false);
    }
    
}

AActor * UTriggerComponent::GetAcceptableActor() const
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);
    for (AActor * Actor : Actors)
    {
        bool HasAcceptableTag = Actor->ActorHasTag(AcceptableActorTag);
        bool IsGrabbed = Actor->ActorHasTag("Grabbed");
        if (HasAcceptableTag && !IsGrabbed)
        {
            return Actor;
        }
    }
    // safe to return null 
    return nullptr;
}

void UTriggerComponent::SetMover(class UMover* InjectedMover)
{
    Mover = InjectedMover;
}

