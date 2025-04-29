#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DelegateData.generated.h"

UCLASS()
class SNAKEGAMEUNREAL_API UDelegateData : public UObject
{
	GENERATED_BODY()

public:
	UDelegateData(const FObjectInitializer& ObjectInitializer){}
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAppleEaten, APlayerPawnBase*, PlayerPawn);
	UPROPERTY()
	FOnAppleEaten OnAppleEaten;
};
