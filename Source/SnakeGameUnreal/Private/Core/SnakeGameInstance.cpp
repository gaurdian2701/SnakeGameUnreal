#include "Core/SnakeGameInstance.h"
#include "Subsystems/InstanceSubsystems/PersistentData_Instance_Subsystem.h"

void USnakeGameInstance::Init()
{
	Super::Init();
	m_persistentDataSubsystem = GetSubsystem<UPersistentData_Instance_Subsystem>();
	m_persistentDataSubsystem->SetGameData(m_snakeGameData);
}

void USnakeGameInstance::SetGameDifficulty(GameDifficultyEnum GameDifficulty)
{
	m_currentGameDifficulty = GameDifficulty;
}

GameDifficultyEnum USnakeGameInstance::GetGameDifficulty() const
{
	return m_currentGameDifficulty;
}



