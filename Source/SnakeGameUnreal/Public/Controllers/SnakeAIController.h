#pragma once
#include "CoreMinimal.h"
#include "GameSystems/UAppleSpawner.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Pawns/PlayerPawnBase.h"
#include "SnakeAIController.generated.h"

UCLASS()
class SNAKEGAMEUNREAL_API ASnakeAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASnakeAIController();
	virtual void Tick(float DeltaTime) override;


protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void GetNextAppleLocation();
	UFUNCTION()
	void OnPlayerDied();
	
	UPROPERTY()
	TObjectPtr<ASnakeGameState> m_snakeGameState;
	UPROPERTY()
	TObjectPtr<APlayerPawnBase> m_snakePawn;
	UPROPERTY()
	TObjectPtr<UAppleSpawner> m_AppleSpawner;
	UPROPERTY()
	TObjectPtr<AActor> m_currentAppleTarget;
	UPROPERTY()
	FVector m_nextAppleLocation;

private:
	FName m_appleEatenSubscriberName = GET_FUNCTION_NAME_CHECKED(ASnakeAIController, GetNextAppleLocation);
	FName m_playerDiedSubscriberName = GET_FUNCTION_NAME_CHECKED(ASnakeAIController, OnPlayerDied);
	
	void SubscribeToEvents();
	void UnsubscribeFromEvents();
};
