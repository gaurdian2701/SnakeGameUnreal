#include "BodyGrowingComponent.h"


UBodyGrowingComponent::UBodyGrowingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBodyGrowingComponent::BeginPlay()
{
	Super::BeginPlay();
	m_mainHead = GetOwner();
}


void UBodyGrowingComponent::AddNewBodySegment()
{
	TObjectPtr<ABodySegmentBase> bodySegment = GetWorld()->
	SpawnActor<ABodySegmentBase>(m_bodySegmentDefaultBlueprint, m_mainHead->GetActorLocation(), FRotator::ZeroRotator,
		FActorSpawnParameters());

	if (m_bodySegments.Num() < 1)
		bodySegment->SetTargetActor(m_mainHead);
	else
		bodySegment->SetTargetActor(m_bodySegments.Last().Get());
	
	m_bodySegments.Add(bodySegment); 
}


