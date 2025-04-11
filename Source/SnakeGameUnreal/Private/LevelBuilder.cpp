#include "LevelBuilder.h"


ALevelBuilder::ALevelBuilder()
{
	PrimaryActorTick.bCanEverTick = true;
	m_world = GetWorld();
}

void ALevelBuilder::BeginPlay()
{
	Super::BeginPlay();
	
	PlaceFloorsAndCeiling();
	// PlaceWalls();
}

void ALevelBuilder::PlaceFloorsAndCeiling()
{
	FVector nextFloorOrCeilingMeshLocation = FVector::ZeroVector;
	nextFloorOrCeilingMeshLocation.X = m_roomLength / 2 * FLOOR_SCALING_VALUE;
	nextFloorOrCeilingMeshLocation.Y = m_roomWidth / 2 * FLOOR_SCALING_VALUE;
	
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	TObjectPtr<AActor> wall = m_world->SpawnActor<AActor>(m_wallBlueprint, FVector::ZeroVector, FRotator::ZeroRotator);
	
	m_roomHeight = wall->FindComponentByClass<UStaticMeshComponent>()->GetComponentScale().Z * FLOOR_SCALING_VALUE;
	m_wallWidth = wall->FindComponentByClass<UStaticMeshComponent>()->GetComponentScale().X * FLOOR_SCALING_VALUE;
	m_world->DestroyActor(wall);

	m_floor_and_ceiling_tile = m_world->SpawnActor<AStaticMeshActor>(nextFloorOrCeilingMeshLocation, FRotator::ZeroRotator);
	StaticMeshComponent = m_floor_and_ceiling_tile->GetStaticMeshComponent();
	StaticMeshComponent->SetStaticMesh(m_floorStaticMesh);
	
}

void ALevelBuilder::PlaceWalls()
{
	FVector nextWallLocation = FVector::ZeroVector;
	for (unsigned short i = 0; i < m_roomLength; i++)
	{
		m_world->SpawnActor<AActor>(m_wallBlueprint, nextWallLocation, FRotator::ZeroRotator);
		nextWallLocation.Y = m_roomWidth * FLOOR_SCALING_VALUE;
		m_world->SpawnActor<AActor>(m_wallBlueprint, nextWallLocation, FRotator::ZeroRotator);
		nextWallLocation.X += m_wallWidth;
		nextWallLocation.Y = 0.0f;
	}

	nextWallLocation = FVector::ZeroVector;
	nextWallLocation.Y += m_wallWidth;
	
	for (unsigned short i = 0; i < m_roomWidth; i++)
	{
		m_world->SpawnActor<AActor>(m_wallBlueprint, nextWallLocation, FRotator::ZeroRotator);
		nextWallLocation.X += m_roomLength * FLOOR_SCALING_VALUE;
		m_world->SpawnActor<AActor>(m_wallBlueprint, nextWallLocation, FRotator::ZeroRotator);
		nextWallLocation.Y += m_wallWidth;
		nextWallLocation.X = 0.0f;
	}
}



void ALevelBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

