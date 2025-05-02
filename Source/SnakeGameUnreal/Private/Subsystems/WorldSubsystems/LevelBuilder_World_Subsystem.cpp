#include "Subsystems/WorldSubsystems/LevelBuilder_World_Subsystem.h"

#include "Core/SnakeGameInstance.h"
#include "Subsystems/InstanceSubsystems/PersistentData_Instance_Subsystem.h"
#include "DataAssets/SnakeGameDataAsset.h"
#include "GameSystems/GridSystem.h"

void ULevelBuilder_World_Subsystem::BeginPlay()
{
	Init();
	PlaceFloorsAndCeiling();
	PlaceWalls();
	SpawnObstacles();
}

TObjectPtr<UGridSystem> ULevelBuilder_World_Subsystem::GetGridSystem()
{
	return m_gridSystem;
}

FORCEINLINE float ULevelBuilder_World_Subsystem::GetRoomHeight()
{
	return m_roomHeight;
}

void ULevelBuilder_World_Subsystem::Init()
{
	const TObjectPtr<USnakeGameDataAsset> GameDataAsset = GetWorld()->GetGameInstance()
	                                                                ->GetSubsystem<UPersistentData_Instance_Subsystem>()
	                                                                ->GetGameData();

	m_wallBlueprint = GameDataAsset->m_WallBlueprint;
	m_floorStaticMesh = GameDataAsset->m_FloorStaticMesh;
	FRoomData DesiredRoomData = GetDifficultyParams(GameDataAsset);
	m_roomLength = DesiredRoomData.m_roomLength;
	m_roomWidth = DesiredRoomData.m_roomLength;
	m_floorMeshOffset = GameDataAsset->m_FloorMeshOffset;

	m_gridSystem = NewObject<UGridSystem>(this);
	m_gridSystem->InitGrid(m_roomLength, m_roomWidth);
}

FRoomData ULevelBuilder_World_Subsystem::GetDifficultyParams(TObjectPtr<USnakeGameDataAsset> DataAsset)
{
	switch (Cast<USnakeGameInstance>(GetWorld()->GetGameInstance())->GetGameDifficulty())
	{
	case GameDifficultyEnum::EASY:
		return DataAsset->m_RoomDataEasyMode;
	case GameDifficultyEnum::MEDIUM:
		return DataAsset->m_RoomDataMediumMode;
	case GameDifficultyEnum::HARD:
		return DataAsset->m_RoomDataHardMode;
	}
	return DataAsset->m_RoomDataEasyMode;
}


void ULevelBuilder_World_Subsystem::PlaceFloorsAndCeiling()
{
	FVector nextFloorOrCeilingMeshLocation = FVector(m_roomLength / 2 * BUILDER_SCALING_VALUE,
	                                                 m_roomWidth / 2 * BUILDER_SCALING_VALUE, 0);
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	TObjectPtr<AActor> wall = GetWorld()->SpawnActor<AActor>(m_wallBlueprint);
	TObjectPtr<UStaticMeshComponent> wallStaticMeshComponent = wall->GetComponentByClass<UStaticMeshComponent>();

	m_roomHeight = wallStaticMeshComponent->GetComponentScale().Z * BUILDER_SCALING_VALUE;
	m_wallWidth = wallStaticMeshComponent->GetComponentScale().X * BUILDER_SCALING_VALUE;

	GetWorld()->DestroyActor(wall);

	m_floor_and_ceiling_tile = GetWorld()->SpawnActor<AStaticMeshActor>(nextFloorOrCeilingMeshLocation,
	                                                                    FRotator::ZeroRotator);
	FVector floorScale = FVector(m_roomLength, m_roomWidth, 1);

	StaticMeshComponent = m_floor_and_ceiling_tile->GetStaticMeshComponent();
	StaticMeshComponent->SetStaticMesh(m_floorStaticMesh);
	m_floor_and_ceiling_tile->SetActorScale3D(floorScale);

	nextFloorOrCeilingMeshLocation.Z = m_roomHeight;

	m_floor_and_ceiling_tile = GetWorld()->SpawnActor<AStaticMeshActor>(nextFloorOrCeilingMeshLocation,
	                                                                    FRotator(180, 0, 0));
	StaticMeshComponent = m_floor_and_ceiling_tile->GetStaticMeshComponent();
	StaticMeshComponent->CastShadow = true;
	StaticMeshComponent->SetStaticMesh(m_floorStaticMesh);
	m_floor_and_ceiling_tile->SetActorScale3D(floorScale);
}

void ULevelBuilder_World_Subsystem::PlaceWalls()
{
	m_gridSystem->PlaceBoundaries(m_wallBlueprint);
}

void ULevelBuilder_World_Subsystem::SpawnObstacles()
{
	int32 columnIndex = 0;
	for (int32 rowIndex = 0; rowIndex < m_roomLength; rowIndex++)
	{
		columnIndex = FMath::RandRange(0, m_roomWidth-1);
		m_gridSystem->SpawnActorAtIndex(m_wallBlueprint, rowIndex, columnIndex, 0);
	}
}
