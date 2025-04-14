#include "LevelBuilder.h"

void ULevelBuilder::Init(UWorld* World, TObjectPtr<USnakeGameDataAsset> GameData)
{
	m_world = World;
	m_wallBlueprint = GameData->m_wallBlueprint;
	m_floorStaticMesh = GameData->m_floorStaticMesh;
	m_roomLength = GameData->RoomData[0].m_roomLength;
	m_roomWidth = GameData->RoomData[0].m_roomWidth;
	m_floorMeshOffset = GameData->m_floorMeshOffset;

	checkf(m_wallBlueprint, TEXT("wall blueprint null"));
	checkf(m_floorStaticMesh, TEXT("floor mesh null"));
	checkf(m_world, TEXT("world null"));
}

void ULevelBuilder::BeginPlay()
{
	PlaceFloorsAndCeiling();
}

void ULevelBuilder::PlaceFloorsAndCeiling()
{
	FVector nextFloorOrCeilingMeshLocation = FVector(m_roomLength / 2 * FLOOR_SCALING_VALUE, m_roomWidth / 2 * FLOOR_SCALING_VALUE, 0);
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UStaticMeshComponent* wallStaticMeshComponent =
		m_wallBlueprint.GetDefaultObject()->FindComponentByClass<UStaticMeshComponent>();
	
	m_roomHeight = wallStaticMeshComponent->GetComponentScale().Z * FLOOR_SCALING_VALUE;
	m_wallWidth = wallStaticMeshComponent->GetComponentScale().X * FLOOR_SCALING_VALUE;
	
	m_floor_and_ceiling_tile = m_world->SpawnActor<AStaticMeshActor>(nextFloorOrCeilingMeshLocation, FRotator::ZeroRotator);
	FVector floorScale = m_floor_and_ceiling_tile->GetActorScale() * FLOOR_SCALING_VALUE;
	
	StaticMeshComponent = m_floor_and_ceiling_tile->GetStaticMeshComponent();
	StaticMeshComponent->SetStaticMesh(m_floorStaticMesh);
	m_floor_and_ceiling_tile->SetActorScale3D(floorScale);
	
	nextFloorOrCeilingMeshLocation.Z = m_roomHeight;
	
	m_floor_and_ceiling_tile = m_world->SpawnActor<AStaticMeshActor>(nextFloorOrCeilingMeshLocation, FRotator(180, 0, 0));
	StaticMeshComponent = m_floor_and_ceiling_tile->GetStaticMeshComponent();
	StaticMeshComponent->CastShadow = false;
	StaticMeshComponent->SetStaticMesh(m_floorStaticMesh);
	m_floor_and_ceiling_tile->SetActorScale3D(floorScale);
}

void ULevelBuilder::PlaceWalls()
{
	FVector nextWallLocation = FVector(m_roomLength / 2 * FLOOR_SCALING_VALUE, 0, 0);
	FVector wallScale = FVector::ZeroVector;
	
	TObjectPtr<AActor> wallActor = nullptr;
	
	wallActor = m_world->SpawnActor<AActor>(m_wallBlueprint, nextWallLocation, FRotator::ZeroRotator);
	wallScale = wallActor->GetActorScale();
	wallScale.X *= m_roomLength;
	wallActor->SetActorScale3D(wallScale);
	
	nextWallLocation.Y = m_roomWidth * FLOOR_SCALING_VALUE;
	
	wallActor = m_world->SpawnActor<AActor>(m_wallBlueprint, nextWallLocation, FRotator::ZeroRotator);
	wallActor->SetActorScale3D(wallScale);

	nextWallLocation.X = 0.0f;
	nextWallLocation.Y = m_roomWidth / 2 * FLOOR_SCALING_VALUE;

	wallActor = m_world->SpawnActor<AActor>(m_wallBlueprint, nextWallLocation, FRotator::ZeroRotator);
	wallScale = wallActor->GetActorScale();
	wallScale.Y *= m_roomWidth;
	wallActor->SetActorScale3D(wallScale);

	nextWallLocation.X = m_roomLength * FLOOR_SCALING_VALUE;

	wallActor = m_world->SpawnActor<AActor>(m_wallBlueprint, nextWallLocation, FRotator::ZeroRotator);
	wallActor->SetActorScale3D(wallScale);
}

