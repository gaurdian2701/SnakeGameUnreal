#include "ABodySegmentBase.h"

ABodySegmentBase::ABodySegmentBase()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false);
}

void ABodySegmentBase::BeginPlay()
{
	Super::BeginPlay();
}

void ABodySegmentBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	m_targetActor = nullptr;
}

void ABodySegmentBase::SetTargetActor(TObjectPtr<AActor> TargetActor)
{
	m_targetActor = TargetActor;
	SetActorTickEnabled(true);
}


void ABodySegmentBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(FMath::Lerp(GetActorLocation(), m_targetActor->GetActorLocation(), DeltaTime * m_lerpSpeed));
}


