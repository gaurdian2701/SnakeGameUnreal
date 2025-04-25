#pragma once
#include "CoreMinimal.h"
#include "Pawns/PlayerPawnBase.h"
#include "Subsystems/WorldSubsystems/LevelBuilder_World_Subsystem.h"
#include "Subsystems/WorldSubsystems/Spawning_World_Subsystem.h"
#include "GameFramework/GameMode.h"
#include "SnakePlayingGameModeBase.generated.h"


UCLASS(Abstract)
class SNAKEGAMEUNREAL_API ASnakePlayingGameModeBase : public AGameMode
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
	
protected:
	virtual void BeginPlay() override;
};
