#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DelegateData.generated.h"

UCLASS()
class SNAKEGAMEUNREAL_API UDelegateData : public UObject
{
	GENERATED_BODY()

private:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAppleEaten, APlayerPawnBase*, PlayerPawn);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Snake Events")
	FOnAppleEaten OnAppleEaten;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDied);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Snake Events")
	FOnPlayerDied OnPlayerDied;


public:
	UDelegateData(const FObjectInitializer& ObjectInitializer){}

	FOnAppleEaten& GetOnAppleEatenDelegate();
	FOnPlayerDied& GetOnPlayerDiedDelegate();
};
