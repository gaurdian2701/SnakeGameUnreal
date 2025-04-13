#include "SnakeGameInstance.h"

void USnakeGameInstance::Init()
{
	m_AppleSpawner = NewObject<UAppleSpawner>();
}

const TObjectPtr<UAppleSpawner> USnakeGameInstance::GetAppleSpawner() const
{
	return *m_AppleSpawner;
}
