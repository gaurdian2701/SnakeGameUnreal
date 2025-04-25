#include "Core/SnakeCooperative_GameMode.h"


void ASnakeCooperative_GameMode::BeginPlay()
{
	Super::BeginPlay();
	CreateNewPlayer();
}

void ASnakeCooperative_GameMode::CreateNewPlayer()
{
	FString errorString;
	GetGameInstance()->CreateLocalPlayer(-1, errorString, true);
}