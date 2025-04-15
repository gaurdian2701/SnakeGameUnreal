#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SnakeGameInstance.generated.h"

class USnakeGameDataAsset;
class ULevelBuilder;
class UAppleSpawner;

UCLASS(Abstract)
class SNAKEGAMEUNREAL_API USnakeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	const TObjectPtr<UAppleSpawner> GetAppleSpawner() const;
	const TObjectPtr<ULevelBuilder> GetLevelBuilder() const;
	const TObjectPtr<USnakeGameDataAsset> GetGameData() const;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameData")
	TObjectPtr<USnakeGameDataAsset> m_snakeGameData;

	virtual void Init() override;

private:
	UPROPERTY()
	TObjectPtr<UAppleSpawner> m_AppleSpawner;
	UPROPERTY()
	TObjectPtr<ULevelBuilder> m_LevelBuilder;
};
