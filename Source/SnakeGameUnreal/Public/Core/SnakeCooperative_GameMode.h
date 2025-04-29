#pragma once

#include "CoreMinimal.h"
#include "SnakePlayingGameModeBase.h"
#include "Pawns/PlayerPawnBase.h"
#include "SnakeCooperative_GameMode.generated.h"

UCLASS(Blueprintable)
class SNAKEGAMEUNREAL_API ASnakeCooperative_GameMode : public ASnakePlayingGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;

private:
	void CreateNewPlayer();
};
