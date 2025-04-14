#include "SnakePlayingGameMode.h"
#include "SnakeGameInstance.h"
void ASnakePlayingGameMode::StartPlay()
{
	Super::StartPlay();
	m_appleSpawner = Cast<USnakeGameInstance>(GetWorld()->GetGameInstance())->GetAppleSpawner();
	m_levelBuilder = Cast<USnakeGameInstance>(GetWorld()->GetGameInstance())->GetLevelBuilder();
}

void ASnakePlayingGameMode::BeginPlay()
{
	Super::BeginPlay();
	m_levelBuilder->Init(GetWorld(), m_SnakeGameData);
	m_levelBuilder->BeginPlay();
}
