#pragma once

#include "CoreMinimal.h"
#include "SnakeGameDataAsset.h"
#include "GameFramework/Actor.h"
#include "GridSystem.h"
#include "UAppleSpawner.generated.h"

class AApple;

UCLASS()
class SNAKEGAMEUNREAL_API UAppleSpawner : public UObject
{
	GENERATED_BODY()

public:
	UAppleSpawner(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer) {}
	void Init(TObjectPtr<USnakeGameDataAsset> GameDataAsset);
	void HandleAppleEaten(AApple* AppleBeingEaten);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAppleEaten);
	UPROPERTY(BlueprintAssignable)
	FOnAppleEaten OnAppleEaten;

private:
	int32 m_appleSpawningHeight = 0;
	
	UPROPERTY()
	TSubclassOf<AActor> m_appleBlueprint;
	UPROPERTY()
	TObjectPtr<UGridSystem> m_gridSystem;
	
	void SpawnNewApple();
};
