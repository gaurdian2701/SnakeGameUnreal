#include "PlayerPawnBase.h"

#include "SnakeGameInstance.h"


APlayerPawnBase::APlayerPawnBase()
{
	PrimaryActorTick.bCanEverTick = true;
	m_snakePawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Snake Pawn Movement"));
}

void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();
	m_appleSpawner = Cast<USnakeGameInstance>(GetGameInstance())->GetAppleSpawner();
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
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Player Ate Apple");
}



