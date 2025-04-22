#include "UAppleSpawner.h"
#include "Apple.h"
#include "LevelBuilder_World_Subsystem.h"

void UAppleSpawner::Init(TObjectPtr<USnakeGameDataAsset> GameDataAsset)
{
	m_appleBlueprint = GameDataAsset->m_AppleBlueprint;
	m_gridSystem = GetWorld()->GetSubsystem<ULevelBuilder_World_Subsystem>()->GetGridSystem();
	m_appleSpawningHeight = GetWorld()->GetSubsystem<ULevelBuilder_World_Subsystem>()->GetRoomHeight()/2;
	SpawnNewApple();
}

void UAppleSpawner::HandleAppleEaten(AApple* AppleBeingEaten)
{
	OnAppleEaten.Broadcast();
	m_gridSystem->DestroyActorFromPosition(AppleBeingEaten->GetActorLocation().X, AppleBeingEaten->GetActorLocation().Y);
	SpawnNewApple();
}

void UAppleSpawner::SpawnNewApple()
{
	FIntVector2 spawnPos = m_gridSystem->GetRandomGridIndex();
	m_gridSystem->SpawnActorAtIndex(m_appleBlueprint, spawnPos.X, spawnPos.Y,
		m_appleSpawningHeight);
}



