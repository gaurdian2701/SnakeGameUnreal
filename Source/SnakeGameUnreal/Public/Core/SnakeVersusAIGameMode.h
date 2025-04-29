#pragma once

#include "CoreMinimal.h"
#include "SnakePlayingGameModeBase.h"
#include "Pawns/PlayerPawnBase.h"
#include "Controllers/SnakeAIController.h"
#include "SnakeVersusAIGameMode.generated.h"

UCLASS()
class SNAKEGAMEUNREAL_API ASnakeVersusAIGameMode : public ASnakePlayingGameModeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI Pawn")
	TSubclassOf<APlayerPawnBase> m_AIPawn;
	
	virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;
	void SpawnAIPawn();
};
