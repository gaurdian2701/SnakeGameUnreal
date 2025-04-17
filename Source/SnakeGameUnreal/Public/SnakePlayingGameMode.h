#pragma once
#include "CoreMinimal.h"
#include "LevelBuilder_World_Subsystem.h"
#include "UAppleSpawner.h"
#include "GameFramework/GameMode.h"
#include "SnakePlayingGameMode.generated.h"

UCLASS(Abstract)
class SNAKEGAMEUNREAL_API ASnakePlayingGameMode : public AGameMode
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UAppleSpawner* m_appleSpawner =  nullptr;
	UPROPERTY()
	ULevelBuilder_World_Subsystem* m_levelBuilder = nullptr;
	
protected:
	virtual void BeginPlay() override;
};
