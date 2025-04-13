#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UAppleSpawner.generated.h"

class AApple;

UCLASS()
class SNAKEGAMEUNREAL_API UAppleSpawner : public UObject
{
	GENERATED_BODY()

public:
	UAppleSpawner();
	void HandleAppleEaten(const AApple& AppleBeingEaten);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAppleEaten);
	UPROPERTY(BlueprintAssignable)
	FOnAppleEaten OnAppleEaten;
};
