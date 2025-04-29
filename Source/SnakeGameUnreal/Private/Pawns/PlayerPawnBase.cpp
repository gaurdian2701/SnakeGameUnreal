#include "Pawns/PlayerPawnBase.h"
#include "Subsystems/InstanceSubsystems/PersistentData_Instance_Subsystem.h"
#include "Subsystems/WorldSubsystems/Spawning_World_Subsystem.h"

APlayerPawnBase::APlayerPawnBase()
{
	PrimaryActorTick.bCanEverTick = true;
	m_snakePawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Snake Pawn Movement"));
	m_bodyGrowingComponent = CreateDefaultSubobject<UBodyGrowingComponent>(TEXT("Snake Growing Component"));
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
	m_gameState = Cast<ASnakeGameState>(GetWorld()->GetGameState());
	m_appleSpawner = GetWorld()->GetSubsystem<USpawning_World_Subsystem>()->GetAppleSpawner();
	m_snakeSegmentDefaultBlueprint = GetGameInstance()->GetSubsystem<UPersistentData_Instance_Subsystem>()
	->GetGameData()->m_SnakeSegment;
}

void APlayerPawnBase::SubscribeToEvents()
{
	if (m_gameState == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, "Game State nullptr");
		return;
	}
	m_gameState->SubscribeToDelegate(m_gameState->GetAppleEatenDelegate(), this, m_appleEatenSubscriberName);
}

void APlayerPawnBase::UnsubscribeFromEvents()
{
	if (m_gameState == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, "Game State nullptr");
		return;
	}
	m_gameState->UnsubscribeFromDelegate(m_gameState->GetAppleEatenDelegate(), this, m_appleEatenSubscriberName);
}

void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_snakePawnMovementComponent->AddInputVector(m_moveSpeed * DeltaTime * GetActorForwardVector());
}

void APlayerPawnBase::OnMove(const float& x, const float& y)
{
	APlayerController* currentController = Cast<APlayerController>(GetController());
	FRotator rotation = currentController->GetControlRotation();
	rotation.Yaw += x * m_turnSpeed;
	rotation.Pitch += y * m_turnSpeed;
	currentController->SetControlRotation(rotation);

	FString controllerName = GetController()->GetActorNameOrLabel();
	FString msg = FString::Printf(TEXT("%f, %f"), x, y);
	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, msg);
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, controllerName);
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




