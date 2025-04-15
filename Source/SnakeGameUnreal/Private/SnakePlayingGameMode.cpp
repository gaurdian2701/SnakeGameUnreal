#include "SnakePlayingGameMode.h"
#include "SnakeGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ASnakePlayingGameMode::StartPlay()
{
	Super::StartPlay();


}

void ASnakePlayingGameMode::BeginPlay()
{
	Super::BeginPlay();

	m_gameInstance = Cast<USnakeGameInstance>(UGameplayStatics::GetGameInstance(this));
	m_appleSpawner = m_gameInstance->GetAppleSpawner();
	m_levelBuilder = m_gameInstance->GetLevelBuilder();
	
	m_levelBuilder->Init(m_gameInstance);
	m_levelBuilder->BeginPlay();
}
