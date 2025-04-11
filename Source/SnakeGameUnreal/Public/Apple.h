#pragma once

#include "CoreMinimal.h"
#include "AppleSpawner.h"
#include "GameFramework/Actor.h"
#include "Apple.generated.h"

UCLASS()
class SNAKEGAMEUNREAL_API AApple : public AActor
{
	GENERATED_BODY()

public:
	AApple();
	void Init(TObjectPtr<AAppleSpawner> AppleSpawner);

protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void Tick(float DeltaTime) override;

private:
	TObjectPtr<UWorld> m_world = nullptr;
	TObjectPtr<AAppleSpawner> m_appleSpawner = nullptr;
};
