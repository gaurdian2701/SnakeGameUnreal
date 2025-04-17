#include "SnakePlayingGameMode.h"
#include "Subsystems/GameInstanceSubsystem.h"

void ASnakePlayingGameMode::BeginPlay()
{
	Super::BeginPlay();
	m_levelBuilder = GetWorld()->GetSubsystem<ULevelBuilder_World_Subsystem>();
	m_levelBuilder->BeginPlay();
}
