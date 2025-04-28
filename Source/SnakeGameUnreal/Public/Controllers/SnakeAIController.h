#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "SnakeAIController.generated.h"

UCLASS()
class SNAKEGAMEUNREAL_API ASnakeAIController : public AController
{
	GENERATED_BODY()

public:
	ASnakeAIController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
