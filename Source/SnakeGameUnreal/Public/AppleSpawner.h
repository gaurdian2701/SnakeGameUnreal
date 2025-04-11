#pragma once

#include "CoreMinimal.h"
#include "Apple.h"
#include "GameFramework/Actor.h"
#include "AppleSpawner.generated.h"

class AApple;

UCLASS()
class SNAKEGAMEUNREAL_API AAppleSpawner : public AActor
{
	GENERATED_BODY()

public:
	AAppleSpawner();

protected:
	virtual void BeginPlay() override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAppleEaten);

	UPROPERTY(BlueprintAssignable)
	FOnAppleEaten OnAppleEaten;

public:
	virtual void Tick(float DeltaTime) override;
	void HandleAppleEaten(const AApple& AppleBeingEaten);
};
