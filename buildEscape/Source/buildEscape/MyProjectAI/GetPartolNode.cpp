// Fill out your copyright notice in the Description page of Project Settings.
#include "GetPartolNode.h"
#include "AIController.h"
#include <buildEscape/PatrolRoute.h>
#include "BehaviorTree/BlackboardComponent.h"



/*
*/
EBTNodeResult::Type UGetPartolNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// 获取到角色身上的巡逻点的数组
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	// Warn about empty patrol routes
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("A guard is missing patrol points"));
		return EBTNodeResult::Failed;
	}

	auto blackBoardCom = OwnerComp.GetBlackboardComponent();
	// 获取到当前正在巡逻的索引
	int nowIndex = blackBoardCom->GetValueAsInt(Index.SelectedKeyName);
	UE_LOG(LogTemp, Log, TEXT("Now index:%d"), nowIndex);

	// 将当前巡逻点设置到黑板
	blackBoardCom->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[nowIndex]);

	// 获得下一个index，方便下一次使用
	auto NextIndex = (nowIndex + 1) % PatrolPoints.Num();
	blackBoardCom->SetValueAsInt(Index.SelectedKeyName, NextIndex);
	return EBTNodeResult::Succeeded;
}
