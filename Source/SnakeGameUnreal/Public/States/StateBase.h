#pragma once

#include "CoreMinimal.h"
#include "Interfaces/State.h"
#include "UObject/Object.h"
#include "StateBase.generated.h"

UCLASS()
class SNAKEGAMEUNREAL_API UStateBase : public UObject, public IState
{
	GENERATED_BODY()

public:
	virtual void EnterState_Implementation() override;
	virtual void ExitState_Implementation() override;
	virtual void UpdateState_Implementation() override;
};
