#include "SnakeGameInstance.h"
#include "PersistentData_Instance_Subsystem.h"

void USnakeGameInstance::Init()
{
	Super::Init();
	m_persistentDataSubsystem = GetSubsystem<UPersistentData_Instance_Subsystem>();
	m_persistentDataSubsystem->SetGameData(m_snakeGameData);
}



