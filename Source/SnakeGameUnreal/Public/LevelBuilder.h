#pragma once

#include "CoreMinimal.h"
#include "SnakeGameInstance.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "LevelBuilder.generated.h"

UCLASS()
class SNAKEGAMEUNREAL_API ULevelBuilder : public UObject
{
	GENERATED_BODY()

public:
	ULevelBuilder(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){}
	void Init(TObjectPtr<USnakeGameInstance> SnakeGameInstance);
	void BeginPlay();

protected:
	
	UPROPERTY()
	TSubclassOf<AActor> m_wallBlueprint = nullptr;

	UPROPERTY()
	TObjectPtr<UStaticMesh> m_floorStaticMesh = nullptr;

	UPROPERTY()
	TObjectPtr<AStaticMeshActor> m_floor_and_ceiling_tile = nullptr;

	UPROPERTY()
	TObjectPtr<UWorld> m_world = nullptr;

private:
	float m_roomHeight = 0.0f;
	float m_wallWidth = 0.0f;
	float m_roomLength = 0.0f;
	float m_roomWidth = 0.0f;
	float m_floorMeshOffset = 0.0f;
	constexpr static float FLOOR_SCALING_VALUE = 100.0f;

	FTimerHandle m_spawnFloorAndCeilingTimerHandle;
	FTimerHandle m_spawnWallTimerHandle;
	
	void PlaceFloorsAndCeiling();
	void PlaceWalls();
};
