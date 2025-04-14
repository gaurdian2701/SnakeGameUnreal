#include "SnakeGameInstance.h"

void USnakeGameInstance::Init()
{
	m_AppleSpawner = NewObject<UAppleSpawner>();
	m_LevelBuilder = NewObject<ULevelBuilder>();
}

FORCEINLINE const TObjectPtr<UAppleSpawner> USnakeGameInstance::GetAppleSpawner() const
{
	return *m_AppleSpawner;
}
