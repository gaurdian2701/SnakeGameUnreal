#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Controllers/SnakeAIController.h"
#include "ObstacleAvoidanceComponent.generated.h"
 
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SNAKEGAMEUNREAL_API UObstacleAvoidanceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UObstacleAvoidanceComponent();

protected:
	virtual void BeginPlay() override;
	void CheckForObstacles(float DeltaTime);

	UPROPERTY()
	TObjectPtr<ASnakeAIController> m_snakeAIController;

	UPROPERTY(EditAnywhere, Category = "Trace Start Offset")
	int m_traceStartOffset = 0;

	UPROPERTY(EditAnywhere, Category = "Trace Length")
	int m_traceLength = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Avoidance Speed")
	float m_avoidanceSpeed;

private:
	TObjectPtr<AActor> m_Owner;
	FCollisionObjectQueryParams objectsIncluded;
	FCollisionQueryParams queryParams;
	FHitResult m_snakeHeadCollisionHitResult;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
