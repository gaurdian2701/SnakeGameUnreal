#include "LevelBuilder_World_Subsystem.h"
#include "PersistentData_Instance_Subsystem.h"
#include "SnakeGameDataAsset.h"

void ULevelBuilder_World_Subsystem::BeginPlay()
{
	Init();
	PlaceFloorsAndCeiling();
	PlaceWalls();
}

void ULevelBuilder_World_Subsystem::Init()
{
	const TObjectPtr<USnakeGameDataAsset> GameDataAsset = GetWorld()->GetGameInstance()->GetSubsystem<UPersistentData_Instance_Subsystem>()->GetGameData();
	m_wallBlueprint = GameDataAsset->m_wallBlueprint;
	m_floorStaticMesh = GameDataAsset->m_floorStaticMesh;
	m_roomLength = GameDataAsset->RoomData[0].m_roomLength;
	m_roomWidth = GameDataAsset->RoomData[0].m_roomWidth;
	m_floorMeshOffset = GameDataAsset->m_floorMeshOffset;
}


void ULevelBuilder_World_Subsystem::PlaceFloorsAndCeiling()
{
	FVector nextFloorOrCeilingMeshLocation = FVector(m_roomLength / 2 * FLOOR_SCALING_VALUE, m_roomWidth / 2 * FLOOR_SCALING_VALUE, 0);
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	TObjectPtr<AActor> wall = GetWorld()->SpawnActor<AActor>(m_wallBlueprint);
	TObjectPtr<UStaticMeshComponent> wallStaticMeshComponent = wall->GetComponentByClass<UStaticMeshComponent>();
	
	m_roomHeight = wallStaticMeshComponent->GetComponentScale().Z * FLOOR_SCALING_VALUE;
	m_wallWidth = wallStaticMeshComponent->GetComponentScale().X * FLOOR_SCALING_VALUE;

	GetWorld()->DestroyActor(wall);
	
	m_floor_and_ceiling_tile = GetWorld()->SpawnActor<AStaticMeshActor>(nextFloorOrCeilingMeshLocation, FRotator::ZeroRotator);
	FVector floorScale = m_floor_and_ceiling_tile->GetActorScale() * FLOOR_SCALING_VALUE;
	
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
	FVector nextWallLocation = FVector(m_roomLength / 2 * FLOOR_SCALING_VALUE, 0, 0);
	FVector wallScale = FVector::ZeroVector;
	
	TObjectPtr<AActor> wallActor = nullptr;
	
	wallActor = GetWorld()->SpawnActor<AActor>(m_wallBlueprint, nextWallLocation, FRotator::ZeroRotator);
	wallScale = wallActor->GetActorScale();
	wallScale.X *= m_roomLength;
	wallActor->SetActorScale3D(wallScale);
	
	nextWallLocation.Y = m_roomWidth * FLOOR_SCALING_VALUE;
	
	wallActor = GetWorld()->SpawnActor<AActor>(m_wallBlueprint, nextWallLocation, FRotator::ZeroRotator);
	wallActor->SetActorScale3D(wallScale);

	nextWallLocation.X = 0.0f;
	nextWallLocation.Y = m_roomWidth / 2 * FLOOR_SCALING_VALUE;

	wallActor = GetWorld()->SpawnActor<AActor>(m_wallBlueprint, nextWallLocation, FRotator::ZeroRotator);
	wallScale = wallActor->GetActorScale();
	wallScale.Y *= m_roomWidth;
	wallActor->SetActorScale3D(wallScale);

	nextWallLocation.X = m_roomLength * FLOOR_SCALING_VALUE;

	wallActor = GetWorld()->SpawnActor<AActor>(m_wallBlueprint, nextWallLocation, FRotator::ZeroRotator);
	wallActor->SetActorScale3D(wallScale);
}

