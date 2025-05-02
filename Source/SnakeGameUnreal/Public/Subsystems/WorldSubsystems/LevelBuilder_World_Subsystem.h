#pragma once
#include "CoreMinimal.h"
#include "DataAssets/SnakeGameDataAsset.h"
#include "GameFramework/Actor.h"
#include "Subsystems/WorldSubsystem.h"
#include "Engine/StaticMeshActor.h"
#include "LevelBuilder_World_Subsystem.generated.h"

class UGridSystem;

UCLASS()
class SNAKEGAMEUNREAL_API ULevelBuilder_World_Subsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	constexpr static float BUILDER_SCALING_VALUE = 100.0f;

	void BeginPlay();
	TObjectPtr<UGridSystem> GetGridSystem();
	float GetRoomHeight();


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
	float m_floorMeshOffset = 0.0f;
	
	int m_roomLength = 0;
	int m_roomWidth = 0;

	UPROPERTY()
	TObjectPtr<UGridSystem> m_gridSystem;

	void Init();
	FRoomData GetDifficultyParams(TObjectPtr<USnakeGameDataAsset> DataAsset);
	void PlaceFloorsAndCeiling();
	void PlaceWalls();
	void SpawnObstacles();
};
