#include "Subsystems/InstanceSubsystems/UStateMachineSubsystem.h"

#include "States/GameStates/EndState.h"
#include "States/GameStates/MenuState.h"
#include "States/GameStates/PlayingState.h"

void UStateMachineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	AddStates_Implementation();
	m_currentState = m_StateObjects[UMenuState::StaticClass()];
	m_currentState->EnterState_Implementation();
}

TSoftObjectPtr<UWorld> UStateMachineSubsystem::GetNewLevelToBeLoaded()
{
	return m_newLevelToBeLoaded;
}

void UStateMachineSubsystem::AddStates_Implementation()
{
	IStateMachine::AddStates_Implementation();

	InitializeNewState(UMenuState::StaticClass());
	InitializeNewState(UPlayingState::StaticClass());
	InitializeNewState(UEndState::StaticClass());
}

void UStateMachineSubsystem::InitializeNewState(UClass* stateClass)
{
	UStateBase* newState = NewObject<UStateBase>(this, stateClass);
	newState->InitState(this);
	m_StateObjects.Add(stateClass, newState);
}

void UStateMachineSubsystem::SwitchState_Implementation(const UClass* NewState, const TSoftObjectPtr<UWorld>& NewLevelToBeLoaded)
{
	IStateMachine::SwitchState_Implementation(NewState, NewLevelToBeLoaded);

	m_newLevelToBeLoaded = NewLevelToBeLoaded;
	m_currentState->ExitState_Implementation();
	m_currentState = m_StateObjects[NewState];
	m_currentState->EnterState_Implementation();
}

void UStateMachineSubsystem::UpdateStateMachine_Implementation(float DeltaTime)
{
	IStateMachine::UpdateStateMachine_Implementation(DeltaTime);
	m_currentState->UpdateState_Implementation();
}
