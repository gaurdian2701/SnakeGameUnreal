#include "SnakePlayingGameMode.h"
#include "Subsystems/GameInstanceSubsystem.h"

void ASnakePlayingGameMode::BeginPlay()
{
	Super::BeginPlay();
	GetSubsystems();
	StartSubsystems();
}

void ASnakePlayingGameMode::GetSubsystems()
{
	m_levelBuilder = GetWorld()->GetSubsystem<ULevelBuilder_World_Subsystem>();
	m_spawningSubsystem = GetWorld()->GetSubsystem<USpawning_World_Subsystem>();
}

void ASnakePlayingGameMode::StartSubsystems()
{
	m_levelBuilder->BeginPlay();
	m_spawningSubsystem->BeginPlay();
}
