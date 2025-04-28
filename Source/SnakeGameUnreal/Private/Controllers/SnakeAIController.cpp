#include "Controllers/SnakeAIController.h"


ASnakeAIController::ASnakeAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASnakeAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASnakeAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

