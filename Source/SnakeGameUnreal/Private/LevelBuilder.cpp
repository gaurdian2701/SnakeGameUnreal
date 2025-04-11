#include "LevelBuilder.h"


ALevelBuilder::ALevelBuilder()
{
	PrimaryActorTick.bCanEverTick = false;
	m_world = GetWorld();
}

void ALevelBuilder::BeginPlay()
{
	Super::BeginPlay();
	
	PlaceFloorsAndCeiling();
	PlaceWalls();
}

void ALevelBuilder::PlaceFloorsAndCeiling()
{
	FVector nextFloorOrCeilingMeshLocation = FVector(m_roomLength / 2 * FLOOR_SCALING_VALUE, m_roomWidth / 2 * FLOOR_SCALING_VALUE, 0);
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	TObjectPtr<AActor> wall = m_world->SpawnActor<AActor>(m_wallBlueprint, FVector::ZeroVector, FRotator::ZeroRotator);
	
	m_roomHeight = wall->FindComponentByClass<UStaticMeshComponent>()->GetComponentScale().Z * FLOOR_SCALING_VALUE;
	m_wallWidth = wall->FindComponentByClass<UStaticMeshComponent>()->GetComponentScale().X * FLOOR_SCALING_VALUE;
	m_world->DestroyActor(wall);
	
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

void ALevelBuilder::PlaceWalls()
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



void ALevelBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

