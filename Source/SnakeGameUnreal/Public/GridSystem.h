#pragma once

#include "CoreMinimal.h"
#include "LevelBuilder_World_Subsystem.h"
#include "UObject/Object.h"
#include "GridSystem.generated.h"

USTRUCT()
struct FGridTile
{
	GENERATED_BODY()

	FGridTile()
	{
		XPosition = 0.0f;
		YPosition = 0.0f;
		bOccupied = false;
	}
	
	float XPosition;
	float YPosition;
	bool bOccupied;
};

UCLASS()
class SNAKEGAMEUNREAL_API UGridSystem : public UObject
{
	GENERATED_BODY()

public:
	UGridSystem(const FObjectInitializer& ObjectInitializer){}
	void InitGrid(int32 Rows, int32 Columns);
	TObjectPtr<AActor> SpawnActorAtIndex(TSubclassOf<AActor> Actor, int32 XIndex, int32 YIndex, int32 height);
	void DestroyActorFromPosition(float XPosition, float YPosition);
	FIntVector2 GetRandomGridIndex();
	void PlaceBoundaries(TSubclassOf<AActor>&);

private:
	UPROPERTY()
	TObjectPtr<ULevelBuilder_World_Subsystem> m_levelBuilder;
	
	UPROPERTY()
	TArray<FGridTile> m_gridTiles;
	
	UPROPERTY()
	TMap<int, TObjectPtr<AActor>> m_spawnedActorsInScene;
	
	int32 m_gridRows = 0;
	int32 m_gridColumns = 0;

	int32 GetHash(int32 XIndex, int32 YIndex);
};
