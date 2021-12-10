// Fill out your copyright notice in the Description page of Project Settings.


#include "openDoor.h"

// Sets default values for this component's properties
UopenDoor::UopenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UopenDoor::BeginPlay()
{
	Super::BeginPlay();
	// ...
}


// Called every frame
void UopenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 如果有压力触发器
	if (pressurePlate) {
		TArray<AActor*> overlapActors;
		pressurePlate->GetOverlappingActors(overlapActors);
		float totalMass = 0.0f;
		if (overlapActors.Num() > 0) {
			for (auto actor : overlapActors) {
				totalMass = totalMass + actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
				UE_LOG(LogTemp, Warning, TEXT("%s on Pressure plate:mass is %f"), *actor->GetName(),actor->FindComponentByClass<UPrimitiveComponent>()->GetMass());
			}
			// 达到触发重量，则打开门
			if (totalMass > TriggerMass) {
				UE_LOG(LogTemp,Log,TEXT("%f:touch to trigger mass"), totalMass)
				OpenDoor();
			}
			else {
				UE_LOG(LogTemp, Log, TEXT("totalMass:%f"), totalMass)
			}
		}
		else {
			CloseDoor();
		}
	}
}

