#pragma once

#include "CoreMinimal.h"
#include "States/StateBase.h"
#include "UObject/Object.h"
#include "EndState.generated.h"

UCLASS()
class SNAKEGAMEUNREAL_API UEndState : public UStateBase
{
	GENERATED_BODY()
	
public:
	virtual void EnterState_Implementation() override;
	virtual void UpdateState_Implementation() override;
	virtual void ExitState_Implementation() override;
};
