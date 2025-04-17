#include "Apple.h"
#include "PlayerPawnBase.h"
#include "UAppleSpawner.h"

DEFINE_LOG_CATEGORY(APPLE_LOG);

AApple::AApple()
{
	PrimaryActorTick.bCanEverTick = false;
	m_world = GetWorld();
}

void AApple::Init(TObjectPtr<UAppleSpawner> AppleSpawner)
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
	GEngine->AddOnScreenDebugMessage(0, 3, FColor::Red, "OVERLASP");
	if (Cast<APlayerPawnBase>(OtherActor))
	{
		m_appleSpawner->HandleAppleEaten(this);
	}
}

