#include "Apple.h"


AApple::AApple()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AApple::BeginPlay()
{
	Super::BeginPlay();
}

void AApple::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
}

void AApple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

