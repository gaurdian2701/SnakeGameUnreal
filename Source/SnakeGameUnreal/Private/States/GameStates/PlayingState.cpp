#include "SnakeGameUnreal/Public/States/GameStates/PlayingState.h"
#include "Subsystems/InstanceSubsystems/UStateMachineSubsystem.h"

void UPlayingState::EnterState_Implementation()
{
	Super::EnterState_Implementation();
	UGameplayStatics::OpenLevelBySoftObjectPtr(this,
		Cast<UStateMachineSubsystem>(m_ownerStateMachine.GetObject())->GetNewLevelToBeLoaded());
}

void UPlayingState::UpdateState_Implementation()
{
	Super::UpdateState_Implementation();
}

void UPlayingState::ExitState_Implementation()
{
	Super::ExitState_Implementation();
}
