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
	TObjectPtr<UStateBase> m_currentState = nullptr;
	
	UPROPERTY()
	TMap<UClass*, UStateBase*> m_StateObjects;

public:
	virtual void SwitchState_Implementation(const UClass* NewState) override;
	virtual void UpdateStateMachine_Implementation(float DeltaTime) override;
};
