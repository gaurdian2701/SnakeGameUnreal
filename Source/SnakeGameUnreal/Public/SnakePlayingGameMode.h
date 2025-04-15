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
	
private:
	UPROPERTY()
	UAppleSpawner* m_appleSpawner =  nullptr;
	UPROPERTY()
	ULevelBuilder* m_levelBuilder = nullptr;
	UPROPERTY()
	TObjectPtr<USnakeGameInstance> m_gameInstance = nullptr;
	
protected:
	virtual void StartPlay() override;
	virtual void BeginPlay() override;
};
