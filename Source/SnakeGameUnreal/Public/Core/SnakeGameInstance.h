#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SnakeGameInstance.generated.h"

class USnakeGameDataAsset;
class UPersistentData_Instance_Subsystem;
class ULevelBuilder_World_Subsystem;
class UAppleSpawner;

UCLASS(Abstract)
class SNAKEGAMEUNREAL_API USnakeGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	virtual void Init() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameData")
	TObjectPtr<USnakeGameDataAsset> m_snakeGameData;

	UPROPERTY()
	TObjectPtr<UPersistentData_Instance_Subsystem> m_persistentDataSubsystem;
	UPROPERTY()
	TObjectPtr<ULevelBuilder_World_Subsystem> m_levelBuilderSubsystem;
};
