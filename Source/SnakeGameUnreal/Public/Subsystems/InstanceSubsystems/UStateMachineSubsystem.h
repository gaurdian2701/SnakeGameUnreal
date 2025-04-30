#pragma once

#include "CoreMinimal.h"
#include "Interfaces/StateMachine.h"
#include "States/StateBase.h"
#include "UObject/Object.h"
#include "UStateMachineSubsystem.generated.h"
UCLASS()
class SNAKEGAMEUNREAL_API UStateMachineSubsystem : public UGameInstanceSubsystem, public IStateMachine
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void AddStates_Implementation() override;

	UPROPERTY()
	TSoftObjectPtr<UWorld> m_newLevelToBeLoaded;
	
	UPROPERTY()
	TObjectPtr<UStateBase> m_currentState = nullptr;
	
	UPROPERTY()
	TMap<UClass*, UStateBase*> m_StateObjects;

public:
	UFUNCTION(BlueprintCallable)
	virtual void SwitchState_Implementation(const UClass* NewState, const TSoftObjectPtr<UWorld>& NewLevelToBeLoaded) override;
	virtual void UpdateStateMachine_Implementation(float DeltaTime) override;
	TSoftObjectPtr<UWorld> GetNewLevelToBeLoaded();

private:
	void InitializeNewState(UClass* stateClass);
};


