#include "GridSystem.h"
#include "LevelBuilder_World_Subsystem.h"
#include "Logging/StructuredLog.h"

void UGridSystem::InitGrid(int32 Rows, int32 Columns)
{
	if (m_gridTiles.Num() > 0)
		m_gridTiles.Empty();

	m_levelBuilder = GetWorld()->GetSubsystem<ULevelBuilder_World_Subsystem>();
	m_gridRows = Rows;
	m_gridColumns = Columns;
	m_gridTiles.SetNum(m_gridRows * m_gridColumns);

	int32 tileIndex = 0;
	
	for (int32 i = 0; i < m_gridRows; i++)
		for (int32 j = 0; j < m_gridColumns; j++)
		{
			m_gridTiles[i * m_gridRows + j].XPosition = i * m_levelBuilder->BUILDER_SCALING_VALUE;
			m_gridTiles[i * m_gridRows + j].YPosition = j * m_levelBuilder->BUILDER_SCALING_VALUE;
		}
}

TObjectPtr<AActor> UGridSystem::SpawnActorAtIndex(TSubclassOf<AActor> Actor, int32 XIndex, int32 YIndex, int32 height)
{
	FGridTile* gridTile = &m_gridTiles[XIndex * m_gridRows + YIndex];
	
	if (gridTile->bOccupied)
	{
		UE_LOGFMT(LogTemp, Error, "TILE ALREADY OCCUPIED AT {0},{1}", XIndex, YIndex);
		return nullptr;
	}

	UE_LOGFMT(LogTemp, Warning, "OBJECT SPAWNED AT {0},{1}", XIndex, YIndex);

	TObjectPtr<AActor> spawnedActor = GetWorld()->SpawnActor<AActor>(Actor, FVector(XIndex * m_levelBuilder->BUILDER_SCALING_VALUE,
		YIndex * m_levelBuilder->BUILDER_SCALING_VALUE,height), FRotator::ZeroRotator, FActorSpawnParameters());
	
	gridTile->bOccupied = true;
	gridTile = nullptr;

	m_spawnedActorsInScene.Add(GetHash(XIndex, YIndex), spawnedActor);
	return spawnedActor;
}

void UGridSystem::DestroyActorFromPosition(float XPosition, float YPosition)
{
	int32 XIndex = XPosition/m_levelBuilder->BUILDER_SCALING_VALUE;
	int32 YIndex = YPosition/m_levelBuilder->BUILDER_SCALING_VALUE;
	m_gridTiles[XIndex * m_gridRows + YIndex].bOccupied = false;

	int32 hash = GetHash(XIndex, YIndex);
	
	TObjectPtr<AActor> actorInScene = m_spawnedActorsInScene[hash];
	m_spawnedActorsInScene.Remove(hash);
	GetWorld()->DestroyActor(actorInScene);
	UE_LOGFMT(LogTemp, Warning, "OBJECT DESPAWNED AT {0},{1}", XIndex, YIndex);
}

int32 UGridSystem::GetHash(int32 XIndex, int32 YIndex)
{
	return 32768 * XIndex + YIndex;
}


void UGridSystem::PlaceBoundaries(TSubclassOf<AActor>& Actor)
{
	FVector wallScale = FVector::ZeroVector;
	
	TObjectPtr<AActor> wallActor = SpawnActorAtIndex(Actor, m_gridColumns/2, 0, 0);
	wallScale = wallActor->GetActorScale();
	wallScale.X *= m_gridRows;
	wallActor->SetActorScale3D(wallScale);

	wallActor = SpawnActorAtIndex(Actor, m_gridColumns/2, m_gridRows-1, 0);
	wallActor->SetActorScale3D(wallScale);

	wallActor = SpawnActorAtIndex(Actor, 0, m_gridRows/2, 0);
	wallScale = wallActor->GetActorScale();
	wallScale.Y *= m_gridColumns;
	wallActor->SetActorScale3D(wallScale);

	wallActor = SpawnActorAtIndex(Actor, m_gridColumns-1, m_gridColumns/2, 0);
	wallActor->SetActorScale3D(wallScale);

	for (int32 i = 0; i < m_gridRows; i++)
	{
		m_gridTiles[i].bOccupied = true;
		m_gridTiles[m_gridRows-1 * m_gridColumns + i].bOccupied = true;
	}

	for (int32 i = 0; i < m_gridColumns; i++)
	{
		m_gridTiles[i].bOccupied = true;
		m_gridTiles[m_gridColumns-1 * m_gridRows + i].bOccupied = true;
	}
}

FIntVector2 UGridSystem::GetRandomGridIndex()
{
	FIntVector2 gridPos;
	gridPos = FIntVector2(FMath::RandRange(1, m_gridRows-2),
	FMath::RandRange(1, m_gridColumns-2));
	return gridPos;
}

