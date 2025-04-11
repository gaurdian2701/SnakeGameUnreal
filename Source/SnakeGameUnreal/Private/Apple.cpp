#include "Apple.h"
#include "PlayerPawnBase.h"


AApple::AApple()
{
	PrimaryActorTick.bCanEverTick = false;
	m_world = GetWorld();
}

void AApple::Init(TObjectPtr<AAppleSpawner> AppleSpawner)
{
	m_appleSpawner = AppleSpawner;
}


void AApple::BeginPlay()
{
	Super::BeginPlay();
}

void AApple::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (Cast<APlayerPawnBase>(OtherActor))
	{
		m_appleSpawner->HandleAppleEaten(*this);
	}
}

void AApple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

