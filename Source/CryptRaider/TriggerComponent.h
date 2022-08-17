// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UTriggerComponent();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// dependency injection
	UFUNCTION(BlueprintCallable)
	void SetMover(class UMover* InjectedMover);

private: 
	UPROPERTY(EditAnywhere, Category = "Crypt Component")
	FName AcceptableActorTag;

	AActor * GetAcceptableActor() const;

	class UMover * Mover;
	
};
