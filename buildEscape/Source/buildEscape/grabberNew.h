// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "grabberNew.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDESCAPE_API UgrabberNew : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UgrabberNew();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// 抓物体
	void Grab();
	// 释放物体
	void Release();
	// 设置输入组件
	void SetupInputComponent();
	// 找到线性碰撞对象
	FHitResult GetLineHit();
	// 获取射线的开头
	FVector GetLineStart();
	// 获取射线的结尾
	FVector GetLineEnd();
	// 射线长度
	UPROPERTY(EditAnywhere)  float reach = 500.f;
	// 初始化物理处理组件
	void SetupPhysicsHandleComponent();
	// 物理处理
	UPhysicsHandleComponent* pyHandle;
	// 输入组件
	UInputComponent* input;	
};
