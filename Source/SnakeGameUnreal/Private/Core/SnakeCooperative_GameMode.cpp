#include "Core/SnakeCooperative_GameMode.h"


void ASnakeCooperative_GameMode::BeginPlay()
{
	Super::BeginPlay();
}

APawn* ASnakeCooperative_GameMode::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
	if (GetGameInstance()->GetLocalPlayers().Num() < 2)
		CreateNewPlayer();
	return Super::SpawnDefaultPawnFor_Implementation(NewPlayer, StartSpot);
}

void ASnakeCooperative_GameMode::CreateNewPlayer()
{
	FString errorString;
	ULocalPlayer* newLocalPlayer = GetGameInstance()->CreateLocalPlayer(-1, errorString, false);

	if (!newLocalPlayer)
	{
		UE_LOG(LogTemp, Error, TEXT("%s"), *errorString);
		return;
	}
	
	APlayerController* newLocalPlayerController = GetWorld()->SpawnActor<APlayerController>(PlayerControllerClass);
	if (!newLocalPlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed get player controller from spawn"));
		return;
	}
	
	APawn* newLocalPlayerPawn = GetWorld()->SpawnActor<APlayerPawnBase>(DefaultPawnClass, ChoosePlayerStart(newLocalPlayerController)->GetActorLocation(),
		FRotator::ZeroRotator, FActorSpawnParameters());
	newLocalPlayerController->Possess(newLocalPlayerPawn);
	
	if (!newLocalPlayerController->PlayerCameraManager)
	{
		UE_LOG(LogTemp, Error, TEXT("CAMERA MANAGER SPAWN FAIL"));
	}

	newLocalPlayerController->SetPlayer(newLocalPlayer);
	newLocalPlayerController->SetViewTarget(newLocalPlayerPawn);
}
