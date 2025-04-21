#include "GridSystem.h"
#include "LevelBuilder_World_Subsystem.h"
#include "Logging/StructuredLog.h"

void UGridSystem::InitGrid(int32& Rows, int32& Columns)
{
	if (m_gridTiles.Num() > 0)
		m_gridTiles.Empty();

	m_levelBuilder = GetWorld()->GetSubsystem<ULevelBuilder_World_Subsystem>();
	m_gridRows = Rows;
	m_gridColumns = Columns;
	m_gridTiles.SetNum(m_gridRows * m_gridColumns);
	
	for (int32 i = 0; i < m_gridRows; i++)
		for (int32 j = 0; j < m_gridColumns; j++)
		{
			m_gridTiles[i * m_gridRows + j].XPosition = i * m_levelBuilder->BUILDER_SCALING_VALUE;
			m_gridTiles[i * m_gridRows + j].YPosition = j * m_levelBuilder->BUILDER_SCALING_VALUE;
		}
}

TObjectPtr<AActor> UGridSystem::SpawnActorAtIndex(TSubclassOf<AActor> Actor, int32& XIndex, int32& YIndex, int32& height)
{
	if (XIndex < 0 || XIndex >= m_gridTiles.Num() || YIndex < 0 || YIndex >= m_gridTiles.Num())
	{
		UE_LOGFMT(LogTemp, Error, "INVALID BOUNDS FOR ACTOR PLACEMENT");
		return nullptr;
	}

	FGridTile* gridTile = &m_gridTiles[XIndex * m_gridRows + YIndex];
	
	if (gridTile->bOccupied)
	{
		UE_LOGFMT(LogTemp, Error, "TILE ALREADY OCCUPIED AT {0},{1}", XIndex, YIndex);
		return nullptr;
	}
	
	TObjectPtr<AActor> spawnedActor = GetWorld()->SpawnActor<AActor>(Actor, FVector(XIndex * m_levelBuilder->BUILDER_SCALING_VALUE,
		YIndex * m_levelBuilder->BUILDER_SCALING_VALUE,height), FRotator::ZeroRotator, FActorSpawnParameters());
	
	gridTile->bOccupied = true;
	gridTile = nullptr;

	return spawnedActor;
}

void UGridSystem::PlaceBoundaries(TSubclassOf<AActor>& Actor)
{
	FVector nextWallLocation = FVector(m_gridRows / 2 * m_levelBuilder->BUILDER_SCALING_VALUE, 0, 0);
	FVector wallScale = FVector::ZeroVector;
	
	TObjectPtr<AActor> wallActor = nullptr;
	
	wallActor = GetWorld()->SpawnActor<AActor>(Actor, nextWallLocation, FRotator::ZeroRotator);
	wallScale = wallActor->GetActorScale();
	wallScale.X *= m_gridRows;
	wallActor->SetActorScale3D(wallScale);
	
	nextWallLocation.Y = m_gridColumns * m_levelBuilder->BUILDER_SCALING_VALUE;
	
	wallActor = GetWorld()->SpawnActor<AActor>(Actor, nextWallLocation, FRotator::ZeroRotator);
	wallActor->SetActorScale3D(wallScale);
	
	nextWallLocation.X = 0.0f;
	nextWallLocation.Y = m_gridRows / 2 * m_levelBuilder->BUILDER_SCALING_VALUE;
	
	wallActor = GetWorld()->SpawnActor<AActor>(Actor, nextWallLocation, FRotator::ZeroRotator);
	wallScale = wallActor->GetActorScale();
	wallScale.Y *= m_gridColumns;
	wallActor->SetActorScale3D(wallScale);
	
	nextWallLocation.X = m_gridRows * m_levelBuilder->BUILDER_SCALING_VALUE;
	
	wallActor = GetWorld()->SpawnActor<AActor>(Actor, nextWallLocation, FRotator::ZeroRotator);
	wallActor->SetActorScale3D(wallScale);

	for (int32 i = 0; i < m_gridRows; i++)
	{
		m_gridTiles[i].bOccupied = true;
		m_gridTiles[m_gridRows-1 + i].bOccupied = true;
	}

	for (int32 i = 0; i < m_gridColumns; i++)
	{
		m_gridTiles[i].bOccupied = true;
		m_gridTiles[m_gridColumns-1 + i].bOccupied = true;
	}
}

FIntVector2 UGridSystem::GetRandomGridIndex()
{
	FIntVector2 gridPos;
	while (true)
	{
		gridPos = FIntVector2(FMath::RandRange(1, m_gridRows-1),
			FMath::RandRange(1, m_gridColumns-1));
		if (!m_gridTiles[gridPos.X + gridPos.Y].bOccupied)
			break;
	}
	return gridPos;
}

