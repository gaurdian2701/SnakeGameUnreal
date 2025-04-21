#include "SnakeSegmentBase.h"

ASnakeSegmentBase::ASnakeSegmentBase()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false);
}

void ASnakeSegmentBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASnakeSegmentBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	m_targetActor = nullptr;
}

void ASnakeSegmentBase::SetTargetActor(TObjectPtr<AActor> TargetActor)
{
	m_targetActor = TargetActor;
	SetActorTickEnabled(true);
}


void ASnakeSegmentBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(FMath::Lerp(GetActorLocation(), m_targetActor->GetActorLocation(), DeltaTime * m_lerpSpeed));
}


