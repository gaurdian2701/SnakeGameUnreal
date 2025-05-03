#include "GameSystems/UAppleSpawner.h"
#include "Actors/Apple.h"
#include "Subsystems/WorldSubsystems/LevelBuilder_World_Subsystem.h"

void UAppleSpawner::Init(TObjectPtr<USnakeGameDataAsset> GameDataAsset)
{
	m_snakeGameState = Cast<ASnakeGameState>(GetWorld()->GetGameState());
	m_appleBlueprint = GameDataAsset->m_AppleBlueprint;
	m_gridSystem = GetWorld()->GetSubsystem<ULevelBuilder_World_Subsystem>()->GetGridSystem();
	m_appleSpawningHeight = GetWorld()->GetSubsystem<ULevelBuilder_World_Subsystem>()->GetRoomHeight()/2;
	SpawnMoreApples();
}

void UAppleSpawner::HandleAppleEaten(AApple* AppleBeingEaten, APlayerPawnBase* PlayerWhoAteApple)
{
	m_gridSystem->DestroyActorFromPosition(AppleBeingEaten->GetActorLocation().X, AppleBeingEaten->GetActorLocation().Y);
	m_applesSpawned.Remove(AppleBeingEaten);
	if (++m_appleDespawnCounter == 5)
		SpawnMoreApples();
	m_snakeGameState->GetDelegateData()->GetOnAppleEatenDelegate().Broadcast(PlayerWhoAteApple);
}

void UAppleSpawner::SpawnMoreApples()
{
	m_appleDespawnCounter = 0;
	for (int32 i = 0; i < 5; i++)
	{
		FIntVector2 spawnPos = m_gridSystem->GetRandomGridIndex();
		m_applesSpawned.Add(m_gridSystem->SpawnActorAtIndex(m_appleBlueprint, spawnPos.X, spawnPos.Y, m_appleSpawningHeight));
	}
}

FVector UAppleSpawner::GetNextAppleLocation()
{
	if (m_applesSpawned.Num() > 0)
		return m_applesSpawned[m_applesSpawned.Num() - 1]->GetActorLocation();
	return FVector::ZeroVector;
}




