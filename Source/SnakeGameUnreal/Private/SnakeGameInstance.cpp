#include "SnakeGameInstance.h"

void USnakeGameInstance::Init()
{
	m_AppleSpawner = NewObject<UAppleSpawner>(this);
	m_LevelBuilder = NewObject<ULevelBuilder>(this);
}

FORCEINLINE TObjectPtr<UAppleSpawner> USnakeGameInstance::GetAppleSpawner() const
{
	return m_AppleSpawner;
}

FORCEINLINE TObjectPtr<ULevelBuilder> USnakeGameInstance::GetLevelBuilder() const
{
	return m_LevelBuilder;
}
