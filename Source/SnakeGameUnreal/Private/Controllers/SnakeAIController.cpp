#include "Controllers/SnakeAIController.h"
#include "Subsystems/WorldSubsystems/Spawning_World_Subsystem.h"

ASnakeAIController::ASnakeAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASnakeAIController::BeginPlay()
{
	Super::BeginPlay();
	m_snakeGameState = Cast<ASnakeGameState>(GetWorld()->GetGameState());
	m_AppleSpawner = GetWorld()->GetSubsystem<USpawning_World_Subsystem>()->GetAppleSpawner();
	m_snakePawn = Cast<APlayerPawnBase>(GetPawn());
	GetNextAppleLocation();
	SubscribeToEvents();
}

void ASnakeAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnsubscribeFromEvents();
}

void ASnakeAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator rotatorOfTargetVector = (m_nextAppleLocation - m_snakePawn->GetActorLocation()).Rotation();
	m_snakePawn->SetActorRotation(rotatorOfTargetVector);
}

void ASnakeAIController::GetNextAppleLocation()
{
	m_nextAppleLocation = m_AppleSpawner->GetNextAppleLocation();
}

void ASnakeAIController::SubscribeToEvents()
{
	m_snakeGameState->SubscribeToDelegate(m_snakeGameState->GetAppleEatenDelegate(), this, m_appleEatenSubscriberName);
}

void ASnakeAIController::UnsubscribeFromEvents()
{
	m_snakeGameState->UnsubscribeFromDelegate(m_snakeGameState->GetAppleEatenDelegate(), this, m_appleEatenSubscriberName);
}


