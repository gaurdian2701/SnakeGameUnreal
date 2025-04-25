#include "Subsystems/InstanceSubsystems/PersistentData_Instance_Subsystem.h"


void UPersistentData_Instance_Subsystem::SetGameData(const TObjectPtr<USnakeGameDataAsset> GameData)
{
	m_GameData = GameData;
}

const TObjectPtr<USnakeGameDataAsset> UPersistentData_Instance_Subsystem::GetGameData() const
{
	return m_GameData;
}


