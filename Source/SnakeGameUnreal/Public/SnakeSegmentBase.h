#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeSegmentBase.generated.h"

UCLASS()
class SNAKEGAMEUNREAL_API ASnakeSegmentBase : public AActor
{
	GENERATED_BODY()

public:
	ASnakeSegmentBase();
	virtual void Tick(float DeltaTime) override;
	void SetTargetActor(TObjectPtr<AActor> TargetActor);

protected:
	UPROPERTY(EditAnywhere, Category = "Lerp Speed")
	float m_lerpSpeed = 0.0f;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY()
	TObjectPtr<AActor> m_targetActor = nullptr;
};
