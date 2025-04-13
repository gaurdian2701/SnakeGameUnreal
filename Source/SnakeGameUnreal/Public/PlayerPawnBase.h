#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Move Action")
	TObjectPtr<UInputAction> m_moveAction = nullptr;

	UPROPERTY(EditAnywhere, Category = "Move Speed")
	float m_moveSpeed = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Turn Speed")
	float m_turnSpeed = 0.0f;

	UPROPERTY()
	const UAppleSpawner* m_appleSpawner;
	
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable) void OnMove(const float& x, const float& y);
	UFUNCTION(BlueprintCallable) void OnPlayerAteApple();

private:
	FVector m_currentInputVector = FVector::ZeroVector;

};
