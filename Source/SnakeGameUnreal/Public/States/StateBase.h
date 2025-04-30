#pragma once

#include "CoreMinimal.h"
#include "Interfaces/State.h"
#include "Interfaces/StateMachine.h"
#include "UObject/Object.h"
#include "StateBase.generated.h"

UCLASS()
class SNAKEGAMEUNREAL_API UStateBase : public UObject, public IState
{
	GENERATED_BODY()

public:
	UStateBase(const FObjectInitializer& ObjectInitializer){}
	void InitState(const TScriptInterface<IStateMachine> OnwerStateMachiine);
	virtual void EnterState_Implementation() override;
	virtual void ExitState_Implementation() override;
	virtual void UpdateState_Implementation() override;

protected:
	TScriptInterface<IStateMachine> m_ownerStateMachine;
};
