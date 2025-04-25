#include "Subsystems/WorldSubsystems/LevelBuilder_World_Subsystem.h"
#include "Subsystems/InstanceSubsystems/PersistentData_Instance_Subsystem.h"
#include "DataAssets/SnakeGameDataAsset.h"
#include "GameSystems/GridSystem.h"

void ULevelBuilder_World_Subsystem::BeginPlay()
{
	Init();
	PlaceFloorsAndCeiling();
	PlaceWalls();
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
	->GetSubsystem<UPersistentData_Instance_Subsystem>()->GetGameData();
	
	m_wallBlueprint = GameDataAsset->m_WallBlueprint;
	m_floorStaticMesh = GameDataAsset->m_FloorStaticMesh;
	m_roomLength = GameDataAsset->m_RoomData[0].m_roomLength;
	m_roomWidth = GameDataAsset->m_RoomData[0].m_roomWidth;
	m_floorMeshOffset = GameDataAsset->m_FloorMeshOffset;

	m_gridSystem = NewObject<UGridSystem>(this);
	m_gridSystem->InitGrid(m_roomLength, m_roomWidth);
}


void ULevelBuilder_World_Subsystem::PlaceFloorsAndCeiling()
{
	FVector nextFloorOrCeilingMeshLocation = FVector(m_roomLength / 2 * BUILDER_SCALING_VALUE, m_roomWidth / 2 * BUILDER_SCALING_VALUE, 0);
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	TObjectPtr<AActor> wall = GetWorld()->SpawnActor<AActor>(m_wallBlueprint);
	TObjectPtr<UStaticMeshComponent> wallStaticMeshComponent = wall->GetComponentByClass<UStaticMeshComponent>();
	
	m_roomHeight = wallStaticMeshComponent->GetComponentScale().Z * BUILDER_SCALING_VALUE;
	m_wallWidth = wallStaticMeshComponent->GetComponentScale().X * BUILDER_SCALING_VALUE;

	GetWorld()->DestroyActor(wall);
	
	m_floor_and_ceiling_tile = GetWorld()->SpawnActor<AStaticMeshActor>(nextFloorOrCeilingMeshLocation, FRotator::ZeroRotator);
	FVector floorScale = FVector(m_roomLength, m_roomWidth, 1);
	
	StaticMeshComponent = m_floor_and_ceiling_tile->GetStaticMeshComponent();
	StaticMeshComponent->SetStaticMesh(m_floorStaticMesh);
	m_floor_and_ceiling_tile->SetActorScale3D(floorScale);
	
	nextFloorOrCeilingMeshLocation.Z = m_roomHeight;
	
	m_floor_and_ceiling_tile = GetWorld()->SpawnActor<AStaticMeshActor>(nextFloorOrCeilingMeshLocation, FRotator(180, 0, 0));
	StaticMeshComponent = m_floor_and_ceiling_tile->GetStaticMeshComponent();
	StaticMeshComponent->CastShadow = false;
	StaticMeshComponent->SetStaticMesh(m_floorStaticMesh);
	m_floor_and_ceiling_tile->SetActorScale3D(floorScale);
}

void ULevelBuilder_World_Subsystem::PlaceWalls()
{
	m_gridSystem->PlaceBoundaries(m_wallBlueprint);
}

