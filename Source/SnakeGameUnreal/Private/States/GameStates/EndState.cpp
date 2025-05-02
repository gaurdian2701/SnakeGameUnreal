#include "SnakeGameUnreal/Public/States/GameStates/EndState.h"

#include "StateInfo/SnakeGameState.h"

void UEndState::EnterState_Implementation()
{
	Super::EnterState_Implementation();
	Cast<ASnakeGameState>(GetWorld()->GetGameState())->GetDelegateData()->GetOnPlayerDiedDelegate().Broadcast();
}

void UEndState::UpdateState_Implementation()
{
	Super::UpdateState_Implementation();
}

void UEndState::ExitState_Implementation()
{
	Super::ExitState_Implementation();
}
