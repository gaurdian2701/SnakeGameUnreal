#pragma once

#include "CoreMinimal.h"
#include "DataAssets/SnakeGameDataAsset.h"
#include "GameFramework/Actor.h"
#include "GridSystem.h"
#include "StateInfo/SnakeGameState.h"
#include "UAppleSpawner.generated.h"

class AApple;
class APlayerPawnBase;

UCLASS()
class SNAKEGAMEUNREAL_API UAppleSpawner : public UObject
{
	GENERATED_BODY()

public:
	UAppleSpawner(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer) {}
	void Init(TObjectPtr<USnakeGameDataAsset> GameDataAsset);
	void HandleAppleEaten(AApple* AppleBeingEaten, APlayerPawnBase* PlayerWhoAteApple);
	FVector GetNextAppleLocation();

private:
	int32 m_appleSpawningHeight = 0;
	int32 m_appleDespawnCounter = 0;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> m_applesSpawned;
	UPROPERTY()
	TSubclassOf<AActor> m_appleBlueprint;
	UPROPERTY()
	TObjectPtr<UGridSystem> m_gridSystem;
	UPROPERTY()
	TObjectPtr<ASnakeGameState> m_snakeGameState;
	
	void SpawnMoreApples();
};
