#pragma once
#include "CoreMinimal.h"
#include "State.h"
#include "UObject/Interface.h"
#include "StateMachine.generated.h"

UINTERFACE()
class UStateMachine : public UInterface
{
	GENERATED_BODY()
};


class SNAKEGAMEUNREAL_API IStateMachine
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddStates();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SwitchState(const UClass* NewState);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateStateMachine(float DeltaTime);
};
