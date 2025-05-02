#include "Core/DelegateData.h"

UDelegateData::FOnAppleEaten& UDelegateData::GetOnAppleEatenDelegate()
{
	return OnAppleEaten;
}

UDelegateData::FOnPlayerDied& UDelegateData::GetOnPlayerDiedDelegate()
{
	return OnPlayerDied;
}
