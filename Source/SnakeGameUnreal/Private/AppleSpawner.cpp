﻿#include "AppleSpawner.h"

AAppleSpawner::AAppleSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAppleSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AAppleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAppleSpawner::HandleAppleEaten(const AApple& AppleBeingEaten)
{
	OnAppleEaten.Broadcast();
}


