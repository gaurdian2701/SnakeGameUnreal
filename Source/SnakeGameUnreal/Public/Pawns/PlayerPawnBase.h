#pragma once
#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Actors/ABodySegmentBase.h"
#include "GameSystems/UAppleSpawner.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "StateInfo/SnakeGameState.h"
#include "PlayerPawnBase.generated.h"

class UObstacleAvoidanceComponent;
class UBodyGrowingComponent;

UCLASS()
class SNAKEGAMEUNREAL_API APlayerPawnBase : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawnBase();
	virtual void Tick(float DeltaTime) override;
	float GetTurnSpeed() const;

protected:
	UPROPERTY()
	TObjectPtr<ASnakeGameState> m_gameState = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UFloatingPawnMovement> m_snakePawnMovementComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBodyGrowingComponent> m_bodyGrowingComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UObstacleAvoidanceComponent> m_obstacleAvoidanceComponent = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Move Action")
	TObjectPtr<UInputAction> m_moveAction = nullptr;

	UPROPERTY(EditAnywhere, Category = "Move Speed")
	float m_moveSpeed = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Turn Speed")
	float m_turnSpeed = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Trace Start Offset")
	int m_traceStartOffset = 0;

	UPROPERTY(EditAnywhere, Category = "Trace Length")
	int m_traceLength = 0;

	UPROPERTY()
	TObjectPtr<UAppleSpawner> m_appleSpawner = nullptr;

	UPROPERTY()
	TSubclassOf<ABodySegmentBase> m_snakeSegmentDefaultBlueprint = nullptr;
	
	UPROPERTY()
	TArray<TObjectPtr<AActor>> m_snakeSegments;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION(BlueprintCallable)
	void OnMove(const float& x, const float& y);
	
	UFUNCTION(BlueprintCallable)
	void OnPlayerAteApple(APlayerPawnBase* playerWhoAteApple);

private:
	FVector m_currentInputVector = FVector::ZeroVector;
	FName m_appleEatenSubscriberName = GET_FUNCTION_NAME_CHECKED(APlayerPawnBase, OnPlayerAteApple);
	FCollisionObjectQueryParams objectsIncluded;
	FCollisionQueryParams queryParams;

	void InitializeProperties();
	void SubscribeToEvents();
	void UnsubscribeFromEvents();
	void AddNewSnakeSegment();
	void CheckIfSnakeIsColliding();
};
