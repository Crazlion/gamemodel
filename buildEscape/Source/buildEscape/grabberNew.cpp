// Fill out your copyright notice in the Description page of Project Settings.


#include "grabberNew.h"

// Sets default values for this component's properties
UgrabberNew::UgrabberNew()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UgrabberNew::BeginPlay()
{
	Super::BeginPlay();
	SetupInputComponent();
	SetupPhysicsHandleComponent();
}


// Called every frame
void UgrabberNew::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	DrawDebugLine(GetWorld(), GetLineStart(), GetLineEnd(), FColor::Blue, 0.f, 0.f, 20.f);
	if (pyHandle && pyHandle->GrabbedComponent) {
		pyHandle->SetTargetLocation(GetLineEnd());
	}
}

void UgrabberNew::Grab()
{
	UE_LOG(LogTemp, Log, TEXT("Grab function is calling"));
	auto hitRes = GetLineHit();
	auto ComponentToGrab = hitRes.GetComponent();
	auto hitActor = hitRes.GetActor();
	if (hitActor) {
		if (pyHandle) {
			UE_LOG(LogTemp,Log,TEXT("hit name:%s"),*hitActor->GetName())
			// 将这个组件变成可抓的
			pyHandle->GrabComponent(
				ComponentToGrab,
				NAME_None,
				ComponentToGrab->GetOwner()->GetActorLocation(),
				true
			);
		}
	}
	else {
		UE_LOG(LogTemp,Warning,TEXT("Line not hit anything!!!"))
	}
}

void UgrabberNew::Release()
{
	UE_LOG(LogTemp, Log, TEXT("Release function is calling"));
	if (!pyHandle) return;
	pyHandle->ReleaseComponent();
}

void UgrabberNew::SetupInputComponent()
{
	// 获得当前角色的输入组件
	if (GetOwner()->InputComponent) {
		input = GetOwner()->InputComponent;
		input->BindAction("grab", IE_Pressed, this, &UgrabberNew::Grab);
		input->BindAction("grab", IE_Released, this, &UgrabberNew::Release);
	}
	else {
		UE_LOG(LogTemp,Error,TEXT("not bind grab"))
	}
}

FHitResult UgrabberNew::GetLineHit()
{
	FHitResult hitRes;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		hitRes,
		GetLineStart(),
		GetLineEnd(),
		FCollisionObjectQueryParams(ECC_PhysicsBody),
		TraceParams
	);
	
	return hitRes;
}

FVector UgrabberNew::GetLineStart()
{
	FVector pLoction;
	FRotator pRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(pLoction,pRotator);
	return pLoction;
}

FVector UgrabberNew::GetLineEnd()
{
	FVector pLoction;
	FRotator pRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(pLoction, pRotator);
	return pLoction + pRotator.Vector() * reach;
}

void UgrabberNew::SetupPhysicsHandleComponent()
{
	pyHandle=GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!pyHandle) {
		UE_LOG(LogTemp, Error, TEXT("can't find UPhysicsHandleComponent"));
	}
}
