#include "Spawning_World_Subsystem.h"

#include "PersistentData_Instance_Subsystem.h"

void USpawning_World_Subsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	m_appleSpawner = NewObject<UAppleSpawner>(this);
}

void USpawning_World_Subsystem::BeginPlay()
{
	m_appleSpawner->Init(GetWorld()->GetGameInstance()->
		GetSubsystem<UPersistentData_Instance_Subsystem>()->GetGameData());
}

TObjectPtr<UAppleSpawner> USpawning_World_Subsystem::GetAppleSpawner()
{
	return m_appleSpawner;
}

 