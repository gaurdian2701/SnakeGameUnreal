#include "SnakeGameInstance.h"
#include "UAppleSpawner.h"
#include "LevelBuilder.h"

void USnakeGameInstance::Init()
{
	m_AppleSpawner = NewObject<UAppleSpawner>(this);
	m_LevelBuilder = NewObject<ULevelBuilder>(this);
	float length = m_snakeGameData->RoomData[0].m_roomLength;
}

const TObjectPtr<UAppleSpawner> USnakeGameInstance::GetAppleSpawner() const
{
	return m_AppleSpawner;
}

const TObjectPtr<ULevelBuilder> USnakeGameInstance::GetLevelBuilder() const
{
	return m_LevelBuilder;
}

const TObjectPtr<USnakeGameDataAsset> USnakeGameInstance::GetGameData() const
{
	return m_snakeGameData;
}

