#pragma once

#include "CoreMinimal.h"
#include "States/StateBase.h"
#include "UObject/Object.h"
#include "PlayingState.generated.h"

UCLASS()
class SNAKEGAMEUNREAL_API UPlayingState : public UStateBase
{
	GENERATED_BODY()

	virtual void EnterState_Implementation() override;
	virtual void UpdateState_Implementation() override;
	virtual void ExitState_Implementation() override;
};


