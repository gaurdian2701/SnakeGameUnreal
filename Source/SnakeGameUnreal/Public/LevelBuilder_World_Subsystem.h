#pragma once
#include "CoreMinimal.h"
#include "SnakeGameInstance.h"
#include "GameFramework/Actor.h"
#include "Subsystems/WorldSubsystem.h"
#include "Engine/StaticMeshActor.h"
#include "LevelBuilder_World_Subsystem.generated.h"

UCLASS()
class SNAKEGAMEUNREAL_API ULevelBuilder_World_Subsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void BeginPlay();

protected:
	UPROPERTY()
	TSubclassOf<AActor> m_wallBlueprint = nullptr;

	UPROPERTY()
	TObjectPtr<UStaticMesh> m_floorStaticMesh = nullptr;

	UPROPERTY()
	TObjectPtr<AStaticMeshActor> m_floor_and_ceiling_tile = nullptr;

private:
	float m_roomHeight = 0.0f;
	float m_wallWidth = 0.0f;
	float m_roomLength = 0.0f;
	float m_roomWidth = 0.0f;
	float m_floorMeshOffset = 0.0f;
	constexpr static float FLOOR_SCALING_VALUE = 100.0f;

	FTimerHandle m_spawnFloorAndCeilingTimerHandle;
	FTimerHandle m_spawnWallTimerHandle;

	void Init();
	void PlaceFloorsAndCeiling();
	void PlaceWalls();
};
