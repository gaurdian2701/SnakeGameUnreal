#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "LevelBuilder.generated.h"

UCLASS()
class SNAKEGAMEUNREAL_API ALevelBuilder : public AActor
{
	GENERATED_BODY()

public:
	ALevelBuilder();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wall Blueprint")
	TSubclassOf<AActor> m_wallBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Floor Static Mesh")
	TObjectPtr<UStaticMesh> m_floorStaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Floor Length(X)")
	float m_roomLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Floor Width(Y)")
	float m_roomWidth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Floor Mesh X Offset")
	float m_floorMeshOffset = 0.0f;
	
	UPROPERTY()
	TObjectPtr<AStaticMeshActor> m_floor_and_ceiling_tile = nullptr;

	UPROPERTY()
	TObjectPtr<UWorld> m_world = nullptr;

private:
	float m_roomHeight;
	float m_wallWidth;
	constexpr static float FLOOR_SCALING_VALUE = 100.0f;
	
	FTimerHandle m_spawnFloorAndCeilingTimerHandle;
	FTimerHandle m_spawnWallTimerHandle;

	UFUNCTION()
	void PlaceFloorsAndCeiling();

	UFUNCTION()
	void PlaceWalls();
};
