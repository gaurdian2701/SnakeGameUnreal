#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SnakeGameInstance.generated.h"

class USnakeGameDataAsset;
class UPersistentData_Instance_Subsystem;
class ULevelBuilder_World_Subsystem;
class UAppleSpawner;

UENUM(BlueprintType)
enum class GameDifficultyEnum : uint8
{
	EASY UMETA(DisplayName = "Easy"),
	MEDIUM UMETA(DisplayName = "Medium"),
	HARD UMETA(DisplayName = "Hard"),
};

UCLASS(Abstract)
class SNAKEGAMEUNREAL_API USnakeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetGameDifficulty(GameDifficultyEnum GameDifficulty);
	UFUNCTION(BlueprintCallable)
	GameDifficultyEnum GetGameDifficulty() const;
	
protected:
	virtual void Init() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameData")
	TObjectPtr<USnakeGameDataAsset> m_snakeGameData;
	UPROPERTY()
	GameDifficultyEnum m_currentGameDifficulty = GameDifficultyEnum::EASY;
	UPROPERTY()
	TObjectPtr<UPersistentData_Instance_Subsystem> m_persistentDataSubsystem;
	UPROPERTY()
	TObjectPtr<ULevelBuilder_World_Subsystem> m_levelBuilderSubsystem;
};
