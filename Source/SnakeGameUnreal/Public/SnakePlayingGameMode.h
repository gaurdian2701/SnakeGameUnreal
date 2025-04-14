#pragma once

#include "CoreMinimal.h"
#include "LevelBuilder.h"
#include "UAppleSpawner.h"
#include "GameFramework/GameMode.h"
#include "SnakePlayingGameMode.generated.h"
UCLASS(Abstract)
class SNAKEGAMEUNREAL_API ASnakePlayingGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ASnakePlayingGameMode(){}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameData")
	TObjectPtr<USnakeGameDataAsset> m_SnakeGameData;
private:
	UPROPERTY()
	TObjectPtr<UAppleSpawner> m_appleSpawner;
	TObjectPtr<ULevelBuilder> m_levelBuilder;
	
protected:
	virtual void StartPlay() override;
	virtual void BeginPlay() override;
};
