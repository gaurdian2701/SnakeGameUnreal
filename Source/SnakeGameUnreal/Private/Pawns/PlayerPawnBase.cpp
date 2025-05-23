﻿#include "Pawns/PlayerPawnBase.h"

#include "Core/SnakeGameInstance.h"
#include "States/GameStates/EndState.h"
#include "Components/ObstacleAvoidanceComponent.h"
#include "Components/BodyGrowingComponent.h"
#include "Subsystems/InstanceSubsystems/PersistentData_Instance_Subsystem.h"
#include "Subsystems/InstanceSubsystems/UStateMachineSubsystem.h"
#include "Subsystems/WorldSubsystems/Spawning_World_Subsystem.h"

APlayerPawnBase::APlayerPawnBase()
{
	PrimaryActorTick.bCanEverTick = true;
	m_snakePawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Snake Pawn Movement"));
	m_bodyGrowingComponent = CreateDefaultSubobject<UBodyGrowingComponent>(TEXT("Snake Growing Component"));
	m_obstacleAvoidanceComponent = CreateDefaultSubobject<UObstacleAvoidanceComponent>(TEXT("Snake Obstacle Avoidance Component"));
}

void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();
	InitializeProperties();
	SubscribeToEvents();
}

void APlayerPawnBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnsubscribeFromEvents();
}

void APlayerPawnBase::InitializeProperties()
{
	queryParams = FCollisionQueryParams(FName(TEXT("Snake Head Collision Trace")), true, GetOwner());
	m_gameState = Cast<ASnakeGameState>(GetWorld()->GetGameState());
	m_appleSpawner = GetWorld()->GetSubsystem<USpawning_World_Subsystem>()->GetAppleSpawner();
	m_snakeSegmentDefaultBlueprint = GetGameInstance()->GetSubsystem<UPersistentData_Instance_Subsystem>()
	                                                  ->GetGameData()->m_SnakeSegment;
	objectsIncluded.AddObjectTypesToQuery(ECC_Pawn);
	objectsIncluded.AddObjectTypesToQuery(ECC_WorldStatic);
	objectsIncluded.AddObjectTypesToQuery(ECC_WorldDynamic);
}

void APlayerPawnBase::SubscribeToEvents()
{
	if (m_gameState == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, "Game State nullptr");
		return;
	}
	m_gameState->SubscribeToDelegate(m_gameState->GetDelegateData()->GetOnAppleEatenDelegate(),
		this, m_appleEatenSubscriberName);
}

void APlayerPawnBase::UnsubscribeFromEvents()
{
	if (m_gameState == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, "Game State nullptr");
		return;
	}
	m_gameState->UnsubscribeFromDelegate(m_gameState->GetDelegateData()->GetOnAppleEatenDelegate(),
		this, m_appleEatenSubscriberName);
}

void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_snakePawnMovementComponent->AddInputVector(m_moveSpeed * DeltaTime * GetActorForwardVector());
	CheckIfSnakeIsColliding();
}

float APlayerPawnBase::GetTurnSpeed() const
{
	return m_turnSpeed;
}

void APlayerPawnBase::OnMove(const float& x, const float& y)
{
	APlayerController* currentController = Cast<APlayerController>(GetController());
	FRotator rotation = currentController->GetControlRotation();
	rotation.Yaw += x * m_turnSpeed;
	rotation.Pitch += y * m_turnSpeed;
	currentController->SetControlRotation(rotation);
}

void APlayerPawnBase::OnPlayerAteApple(APlayerPawnBase* PlayerWhoAteApple)
{
	if (this == PlayerWhoAteApple)
		AddNewSnakeSegment();
}

void APlayerPawnBase::AddNewSnakeSegment()
{
	m_bodyGrowingComponent->AddNewBodySegment();
}

void APlayerPawnBase::CheckIfSnakeIsColliding()
{
	FHitResult snakeHeadCollisionHitResult;
	FVector traceStart = GetActorLocation() + GetActorForwardVector() * GetActorScale().Length() * m_traceStartOffset;
	FVector traceEnd = traceStart + GetActorForwardVector() * m_traceLength;

	if (GetWorld()->LineTraceSingleByObjectType(snakeHeadCollisionHitResult, traceStart, traceEnd, objectsIncluded,
	                                            queryParams))
	{

		Cast<USnakeGameInstance>(GetGameInstance())->GetSubsystem<UStateMachineSubsystem>()->SwitchState_Implementation(UEndState::StaticClass(),
			GetWorld());
	}
}
