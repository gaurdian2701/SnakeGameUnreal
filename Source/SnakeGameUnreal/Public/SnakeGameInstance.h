#pragma once

#include "CoreMinimal.h"
#include "UAppleSpawner.h"
#include "Engine/GameInstance.h"
#include "SnakeGameInstance.generated.h"

UCLASS()
class SNAKEGAMEUNREAL_API USnakeGameInstance : public UGameInstance
{
public:
	const TObjectPtr<UAppleSpawner> GetAppleSpawner() const;
	GENERATED_BODY()

private:
	TObjectPtr<UAppleSpawner> m_AppleSpawner;

protected:
	virtual void Init() override;
};
