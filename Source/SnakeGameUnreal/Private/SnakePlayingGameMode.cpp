#include "SnakePlayingGameMode.h"

void ASnakePlayingGameMode::StartPlay()
{
	Super::StartPlay();
	m_appleSpawner = NewObject<UAppleSpawner>(this);
	m_levelBuilder = NewObject<ULevelBuilder>(this);
	m_levelBuilder->Init(m_SnakeGameData);
}

void ASnakePlayingGameMode::BeginPlay()
{
	Super::BeginPlay();
	m_levelBuilder->BeginPlay();
}
