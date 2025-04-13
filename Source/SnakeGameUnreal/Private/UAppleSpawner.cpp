#include "UAppleSpawner.h"

UAppleSpawner::UAppleSpawner()
{
	
}

void UAppleSpawner::HandleAppleEaten(const AApple& AppleBeingEaten)
{
	OnAppleEaten.Broadcast();
}


