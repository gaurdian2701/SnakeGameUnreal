#include "Actors/Apple.h"
#include "Pawns/PlayerPawnBase.h"
#include "Subsystems/WorldSubsystems/Spawning_World_Subsystem.h"
#include "GameSystems/UAppleSpawner.h"

DEFINE_LOG_CATEGORY(APPLE_LOG);

AApple::AApple()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AApple::BeginPlay()
{
	Super::BeginPlay();
	m_appleSpawner = GetWorld()->GetSubsystem<USpawning_World_Subsystem>()->GetAppleSpawner();
}

void AApple::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (Cast<APlayerPawnBase>(OtherActor))
	{
		m_appleSpawner->HandleAppleEaten(this, Cast<APlayerPawnBase>(OtherActor));
	}
}

