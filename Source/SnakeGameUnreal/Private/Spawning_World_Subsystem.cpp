#include "Spawning_World_Subsystem.h"

void USpawning_World_Subsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	m_appleSpawner = NewObject<UAppleSpawner>(this);
}
 