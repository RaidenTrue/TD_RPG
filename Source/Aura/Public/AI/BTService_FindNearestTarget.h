// Copyright by Savvas JRD - LTD Cyprus

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_FindNearestTarget.generated.h"



/**
 * 
 */
UCLASS()
class AURA_API UBTService_FindNearestTarget : public UBTService_BlueprintBase
{
	GENERATED_BODY()

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBlackboardKeySelector TargetToFollowSelector;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBlackboardKeySelector DistanceToTargetSelector;
	
};
