#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AppleSpawner.generated.h"

UCLASS()
class SNAKEGAMEUNREAL_API AAppleSpawner : public AActor
{
	GENERATED_BODY()

public:
	AAppleSpawner();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
