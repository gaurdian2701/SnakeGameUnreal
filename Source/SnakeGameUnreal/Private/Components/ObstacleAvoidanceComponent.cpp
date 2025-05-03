#include "Components/ObstacleAvoidanceComponent.h"

UObstacleAvoidanceComponent::UObstacleAvoidanceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UObstacleAvoidanceComponent::BeginPlay()
{
	Super::BeginPlay();
	m_snakeAIController = Cast<ASnakeAIController>(Cast<APawn>(GetOwner())->GetController());
	if (!m_snakeAIController)
		SetComponentTickEnabled(false);
	else
		GEngine->AddOnScreenDebugMessage(2, 5, FColor::Red,
			"CAST SUCCESSFUL");
	
	m_Owner = GetOwner();
}

void UObstacleAvoidanceComponent::CheckForObstacles(float DeltaTime)
{
	FVector traceStart = m_Owner->GetActorLocation() + m_Owner->GetActorForwardVector() *
		m_Owner->GetActorScale().Length() * m_traceStartOffset;
	FVector traceEnd = traceStart + m_Owner->GetActorForwardVector() * m_traceLength;

	if (GetWorld()->LineTraceSingleByObjectType(m_snakeHeadCollisionHitResult, traceStart, traceEnd, objectsIncluded,
												queryParams))
	{
		m_snakeAIController->bControlOverridden = true;
		FVector hitNormal = m_snakeHeadCollisionHitResult.Normal;
		FRotator avoidanceRotator = hitNormal.RotateAngleAxis(90.f, FVector::UpVector).Rotation();
		m_snakeAIController->DoOverriddenControllingMovement(FMath::RInterpTo(m_Owner->GetActorRotation(),
			avoidanceRotator, DeltaTime, m_avoidanceSpeed));

		GEngine->AddOnScreenDebugMessage(2, 5, FColor::Red,
								 FString::Printf(
									 TEXT("AI HIT %s"), *m_snakeHeadCollisionHitResult.GetActor()->GetName()));
		DrawDebugLine(GetWorld(), traceStart, traceEnd, FColor::Red, false, -1, 0, 2);
	}
	else
		m_snakeAIController->bControlOverridden = false;
}

void UObstacleAvoidanceComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckForObstacles(DeltaTime);
}

