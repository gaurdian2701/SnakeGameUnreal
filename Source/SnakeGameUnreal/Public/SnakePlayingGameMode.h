#pragma once
#include "CoreMinimal.h"
#include "LevelBuilder_World_Subsystem.h"
#include "Spawning_World_Subsystem.h"
#include "UAppleSpawner.h"
#include "GameFramework/GameMode.h"
#include "SnakePlayingGameMode.generated.h"


UCLASS(Abstract)
class SNAKEGAMEUNREAL_API ASnakePlayingGameMode : public AGameMode
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TObjectPtr<UAppleSpawner> m_appleSpawner =  nullptr;
	UPROPERTY()
	TObjectPtr<ULevelBuilder_World_Subsystem> m_levelBuilder = nullptr;
	UPROPERTY()
	TObjectPtr<USpawning_World_Subsystem> m_spawningSubsystem = nullptr;

	void GetSubsystems();
	void StartSubsystems();
	void CreateNewPlayer();
	
protected:
	virtual void BeginPlay() override;
};
