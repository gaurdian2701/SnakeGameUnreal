#include "UAppleSpawner.h"
#include "Apple.h"

void UAppleSpawner::HandleAppleEaten(AApple* AppleBeingEaten)
{
	OnAppleEaten.Broadcast();
	GetWorld()->DestroyActor(Cast<AActor>(AppleBeingEaten));
}


