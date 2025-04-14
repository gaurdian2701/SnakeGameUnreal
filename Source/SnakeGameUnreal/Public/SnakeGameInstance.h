#pragma once

#include "CoreMinimal.h"
#include "LevelBuilder.h"
#include "UAppleSpawner.h"
#include "Engine/GameInstance.h"
#include "SnakeGameInstance.generated.h"

UCLASS()
class SNAKEGAMEUNREAL_API USnakeGameInstance : public UGameInstance
{
public:
	TObjectPtr<UAppleSpawner> GetAppleSpawner() const;
	TObjectPtr<ULevelBuilder> GetLevelBuilder() const;
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UAppleSpawner> m_AppleSpawner;
	UPROPERTY()
	TObjectPtr<ULevelBuilder> m_LevelBuilder;

protected:
	virtual void Init() override;
};
