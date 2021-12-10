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
	// ץ����
	void Grab();
	// �ͷ�����
	void Release();
	// �����������
	void SetupInputComponent();
	// �ҵ�������ײ����
	FHitResult GetLineHit();
	// ��ȡ���ߵĿ�ͷ
	FVector GetLineStart();
	// ��ȡ���ߵĽ�β
	FVector GetLineEnd();
	// ���߳���
	UPROPERTY(EditAnywhere)  float reach = 500.f;
	// ��ʼ�����������
	void SetupPhysicsHandleComponent();
	// ������
	UPhysicsHandleComponent* pyHandle;
	// �������
	UInputComponent* input;	
};
