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

void UStateMachineSubsystem::AddStates_Implementation()
{
	IStateMachine::AddStates_Implementation();
	m_StateObjects.Add(UMenuState::StaticClass(), NewObject<UMenuState>(this));
	m_StateObjects.Add(UPlayingState::StaticClass(), NewObject<UPlayingState>(this));
	m_StateObjects.Add(UEndState::StaticClass(), NewObject<UEndState>(this));
}

void UStateMachineSubsystem::SwitchState_Implementation(const UClass* NewState)
{
	IStateMachine::SwitchState_Implementation(NewState);
	m_currentState->ExitState_Implementation();
	m_currentState = m_StateObjects[NewState];
	m_currentState->EnterState_Implementation();
}

void UStateMachineSubsystem::UpdateStateMachine_Implementation(float DeltaTime)
{
	IStateMachine::UpdateStateMachine_Implementation(DeltaTime);
}
