#include "UAppleSpawner.h"

void UAppleSpawner::Init(USnakeGameDataAsset GameData)
{
	
}


void UAppleSpawner::HandleAppleEaten(const AApple& AppleBeingEaten)
{
	OnAppleEaten.Broadcast();
}


