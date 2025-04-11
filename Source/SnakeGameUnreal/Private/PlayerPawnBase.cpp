#include "PlayerPawnBase.h"


APlayerPawnBase::APlayerPawnBase()
{
	PrimaryActorTick.bCanEverTick = true;
	m_snakePawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Snake Pawn Movement"));
	m_snakePawnMovementComponent->RegisterComponent();

	//TODO Have to store a reference to AppleSpawner class in order to listen to the event it invokes.
	//Searching for it in scene is not good practice, so I should store references to all objects in a TMap.
	//I could try to do this in GameMode.
}

void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();
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
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "AppleEaten");
}



