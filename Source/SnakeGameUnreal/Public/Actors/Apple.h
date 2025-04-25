#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Apple.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(APPLE_LOG, Log, All)
class UAppleSpawner;

UCLASS()
class SNAKEGAMEUNREAL_API AApple : public AActor
{
	GENERATED_BODY()

public:
	AApple();

protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	TObjectPtr<UAppleSpawner> m_appleSpawner = nullptr;
};
