#pragma once
#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "ABodySegmentBase.h"
#include "BodyGrowingComponent.h"
#include "UAppleSpawner.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PlayerPawnBase.generated.h"

UCLASS()
class SNAKEGAMEUNREAL_API APlayerPawnBase : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawnBase();
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	TObjectPtr<UFloatingPawnMovement> m_snakePawnMovementComponent = nullptr;

	UPROPERTY()
	TObjectPtr<UBodyGrowingComponent> m_bodyGrowingComponent = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Move Action")
	TObjectPtr<UInputAction> m_moveAction = nullptr;

	UPROPERTY(EditAnywhere, Category = "Move Speed")
	float m_moveSpeed = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Turn Speed")
	float m_turnSpeed = 0.0f;

	UPROPERTY()
	TObjectPtr<UAppleSpawner> m_appleSpawner = nullptr;

	UPROPERTY()
	TSubclassOf<ABodySegmentBase> m_snakeSegmentDefaultBlueprint = nullptr;
	
	UPROPERTY()
	TArray<TObjectPtr<AActor>> m_snakeSegments;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	UFUNCTION(BlueprintCallable) void OnMove(const float& x, const float& y);
	UFUNCTION(BlueprintCallable) void OnPlayerAteApple();

private:
	FVector m_currentInputVector = FVector::ZeroVector;

	void InitializeProperties();
	void SubscribeToEvents();
	void UnsubscribeFromEvents();
	void AddNewSnakeSegment();
};
