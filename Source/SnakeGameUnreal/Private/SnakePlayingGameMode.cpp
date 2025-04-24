#include "SnakePlayingGameMode.h"
#include "PlayerPawnBase.h"
#include "Subsystems/GameInstanceSubsystem.h"

void ASnakePlayingGameMode::BeginPlay()
{
	Super::BeginPlay();
	GetSubsystems();
	StartSubsystems();
	CreateNewPlayer();
}

void ASnakePlayingGameMode::GetSubsystems()
{
	m_levelBuilder = GetWorld()->GetSubsystem<ULevelBuilder_World_Subsystem>();
	m_spawningSubsystem = GetWorld()->GetSubsystem<USpawning_World_Subsystem>();
}

void ASnakePlayingGameMode::StartSubsystems()
{
	m_levelBuilder->BeginPlay();
	m_spawningSubsystem->BeginPlay();
}

void ASnakePlayingGameMode::CreateNewPlayer()
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

