#pragma once

#include "CoreMinimal.h"
#include "StateInfo/SnakeGameState.h"
#include "Components/ActorComponent.h"
#include "Actors/ABodySegmentBase.h"
#include "BodyGrowingComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class SNAKEGAMEUNREAL_API UBodyGrowingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBodyGrowingComponent();
	void AddNewBodySegment();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Body Growing Component")
	TSubclassOf<ABodySegmentBase> m_bodySegmentDefaultBlueprint;
	
	UPROPERTY()
	TObjectPtr<AActor> m_mainHead = nullptr;
	
	UPROPERTY()
	TArray<TObjectPtr<AActor>> m_bodySegments;

	UPROPERTY()
	TObjectPtr<ASnakeGameState> m_snakeGameState;
};
