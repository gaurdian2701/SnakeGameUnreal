#include "Core/SnakeVersusAIGameMode.h"

APawn* ASnakeVersusAIGameMode::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
	SpawnAIPawn();
	return Super::SpawnDefaultPawnFor_Implementation(NewPlayer, StartSpot);
}

void ASnakeVersusAIGameMode::SpawnAIPawn()
{
	AController* dummyController = nullptr;
	FVector spawnLocation = ChoosePlayerStart(dummyController)->GetActorLocation();

	TObjectPtr<APlayerPawnBase> spawnedAIPawn = GetWorld()->SpawnActor<APlayerPawnBase>(m_AIPawn, spawnLocation,
		FRotator::ZeroRotator, FActorSpawnParameters());
	spawnedAIPawn->SpawnDefaultController();
}
