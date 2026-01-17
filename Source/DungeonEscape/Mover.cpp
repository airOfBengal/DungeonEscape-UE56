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

	/*AActor* myOwner = GetOwner();
	UE_LOG(LogTemp, Display, TEXT("My owner is called %s"), *myOwner->GetActorNameOrLabel());

	FVector startLocation = myOwner->GetActorLocation();
	UE_LOG(LogTemp, Display, TEXT("My owner's location is: %s"), *startLocation.ToCompactString());*/

	StartLocation = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldMove) 
	{
		SetTargetLocation();
	}
	else
	{
		ResetTargetLocation();
	}

	FVector CurrentLocation = GetOwner()->GetActorLocation();
	ReachedTarget = CurrentLocation.Equals(TargetLocation);
	if (!ReachedTarget)
	{
		float Speed = MoveOffset.Length() / MoveTime;
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		GetOwner()->SetActorLocation(NewLocation);
	}	
}

bool UMover::GetShouldMove()
{
	return ShouldMove;
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
}

void UMover::SetTargetLocation() {
	TargetLocation = StartLocation + MoveOffset;
}

void UMover::ResetTargetLocation() {
	TargetLocation = StartLocation;
}

