﻿#pragma once

#include "CoreMinimal.h"
#include "SnakeGameDataAsset.h"
#include "GameFramework/Actor.h"
#include "UAppleSpawner.generated.h"

class AApple;

UCLASS()
class SNAKEGAMEUNREAL_API UAppleSpawner : public UObject
{
	GENERATED_BODY()

public:
	UAppleSpawner(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer) {}
	void HandleAppleEaten(AApple* AppleBeingEaten);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAppleEaten);
	UPROPERTY(BlueprintAssignable)
	FOnAppleEaten OnAppleEaten;

private:

	UPROPERTY()
	TObjectPtr<UWorld> m_world;
	
	void Init(USnakeGameDataAsset GameData);
	void SpawnNewApple();
};
