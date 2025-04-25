#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "State.generated.h"

UINTERFACE(Blueprintable)
class UState : public UInterface
{
	GENERATED_BODY()
};

class SNAKEGAMEUNREAL_API IState
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EnterState();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ExitState();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateState();
};
