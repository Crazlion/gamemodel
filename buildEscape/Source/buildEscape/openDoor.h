// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Runtime/Engine/Classes/Engine/TriggerBase.h>
#include "openDoor.generated.h"

UCLASS(Blueprintable,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDESCAPE_API UopenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UopenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// 开门
	UFUNCTION(BlueprintImplementableEvent, Category = "Triggerable Door|Door Switch")
		void OpenDoor();
	// 关门
	UFUNCTION(BlueprintImplementableEvent, Category = "Triggerable Door|Door Switch")
		void CloseDoor();

private:
	// 触发器
	UPROPERTY(EditAnywhere) ATriggerBase* pressurePlate=nullptr;
	UPROPERTY(EditAnywhere) float TriggerMass = 50.f;
};
