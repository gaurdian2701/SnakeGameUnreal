#include "Core/SnakePlayingGameModeBase.h"

void ASnakePlayingGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GetSubsystems();
	StartSubsystems();
}

void ASnakePlayingGameModeBase::GetSubsystems()
{
	m_miscFunctions = NewObject<UMiscellaneousFunctions>(this);
	m_levelBuilder = GetWorld()->GetSubsystem<ULevelBuilder_World_Subsystem>();
	m_spawningSubsystem = GetWorld()->GetSubsystem<USpawning_World_Subsystem>();
}

void ASnakePlayingGameModeBase::StartSubsystems()
{
	m_levelBuilder->BeginPlay();
	m_spawningSubsystem->BeginPlay();
}

const TObjectPtr<UMiscellaneousFunctions> ASnakePlayingGameModeBase::GetMiscFunctions() const
{
	return m_miscFunctions;
}




