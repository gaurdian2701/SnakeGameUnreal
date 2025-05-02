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
	FRotator snakeRotation = m_snakePawn->GetActorRotation();
	FRotator targetRotation = FMath::RInterpTo(snakeRotation, rotatorOfTargetVector, DeltaTime, m_snakePawn->GetTurnSpeed());
	m_snakePawn->SetActorRotation(targetRotation);
}

void ASnakeAIController::GetNextAppleLocation()
{
	m_nextAppleLocation = m_AppleSpawner->GetNextAppleLocation();
}

void ASnakeAIController::SubscribeToEvents()
{
	m_snakeGameState->SubscribeToDelegate(m_snakeGameState->GetDelegateData()->GetOnAppleEatenDelegate(),
		this, m_appleEatenSubscriberName);
	m_snakeGameState->SubscribeToDelegate(m_snakeGameState->GetDelegateData()->GetOnPlayerDiedDelegate(),
		this, m_playerDiedSubscriberName);
}

void ASnakeAIController::UnsubscribeFromEvents()
{
	m_snakeGameState->UnsubscribeFromDelegate(m_snakeGameState->GetDelegateData()->GetOnAppleEatenDelegate(),
		this, m_appleEatenSubscriberName);
	m_snakeGameState->UnsubscribeFromDelegate(m_snakeGameState->GetDelegateData()->GetOnPlayerDiedDelegate(),
	this, m_playerDiedSubscriberName);
}

void ASnakeAIController::OnPlayerDied()
{
	m_snakePawn->SetActorTickEnabled(false);
}


