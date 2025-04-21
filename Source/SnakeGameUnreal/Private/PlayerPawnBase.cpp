#include "PlayerPawnBase.h"

#include "PersistentData_Instance_Subsystem.h"
#include "SnakeSegmentBase.h"
#include "Spawning_World_Subsystem.h"

APlayerPawnBase::APlayerPawnBase()
{
	PrimaryActorTick.bCanEverTick = true;
	m_snakePawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Snake Pawn Movement"));
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
	m_appleSpawner = GetWorld()->GetSubsystem<USpawning_World_Subsystem>()->GetAppleSpawner();
	m_snakeSegmentDefaultBlueprint = GetGameInstance()->GetSubsystem<UPersistentData_Instance_Subsystem>()
	->GetGameData()->m_SnakeSegment;
}

void APlayerPawnBase::SubscribeToEvents()
{
	m_appleSpawner->OnAppleEaten.AddDynamic(this, &APlayerPawnBase::OnPlayerAteApple);
}

void APlayerPawnBase::UnsubscribeFromEvents()
{
	m_appleSpawner->OnAppleEaten.RemoveDynamic(this, &APlayerPawnBase::OnPlayerAteApple);
}

void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_snakePawnMovementComponent->AddInputVector(m_moveSpeed * DeltaTime * GetActorForwardVector());
}

void APlayerPawnBase::OnMove(const float& x, const float& y)
{
	AddControllerPitchInput(-y * m_turnSpeed);
	AddControllerYawInput(x * m_turnSpeed);
}

void APlayerPawnBase::OnPlayerAteApple()
{
	AddNewSnakeSegment();
}

void APlayerPawnBase::AddNewSnakeSegment()
{
	TObjectPtr<ASnakeSegmentBase> m_snakeSegment = GetWorld()->
		SpawnActor<ASnakeSegmentBase>(m_snakeSegmentDefaultBlueprint, GetActorLocation(), FRotator::ZeroRotator,
			FActorSpawnParameters());

	if (m_snakeSegments.Num() < 1)
		m_snakeSegment->SetTargetActor(Cast<AActor>(this));
	else
		m_snakeSegment->SetTargetActor(m_snakeSegments.Last().Get());
	
	m_snakeSegments.Add(m_snakeSegment);
}




