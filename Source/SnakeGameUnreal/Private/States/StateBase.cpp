#include "States/StateBase.h"

void UStateBase::InitState(const TScriptInterface<IStateMachine> OwnerStateMachine)
{
	m_ownerStateMachine = OwnerStateMachine;
}

void UStateBase::EnterState_Implementation()
{
	IState::EnterState_Implementation();
}

void UStateBase::ExitState_Implementation()
{
	IState::ExitState_Implementation();
}

void UStateBase::UpdateState_Implementation()
{
	IState::UpdateState_Implementation();
}
