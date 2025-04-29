#include "StateInfo/SnakeGameState.h"

ASnakeGameState::ASnakeGameState()
{
}

void ASnakeGameState::BeginPlay()
{
	Super::BeginPlay();
	m_delegateData = NewObject<UDelegateData>(this);
}

TObjectPtr<UDelegateData> ASnakeGameState::GetDelegateData() const
{
	return m_delegateData;
}

UDelegateData::FOnAppleEaten& ASnakeGameState::GetAppleEatenDelegate() const
{
	return m_delegateData->OnAppleEaten;
}

void ASnakeGameState::SubscribeToDelegate(FMulticastScriptDelegate& DelegateEvent, UObject* SubscriberClass,
	const FName& SubscriberFunctionName)
{
	FScriptDelegate ScriptDelegate;
	ScriptDelegate.BindUFunction(SubscriberClass, SubscriberFunctionName);
	DelegateEvent.AddUnique(ScriptDelegate);
}

void ASnakeGameState::UnsubscribeFromDelegate(FMulticastScriptDelegate& DelegateEvent, UObject* SubscriberClass,
	const FName& SubscriberFunctionName)
{
	FScriptDelegate ScriptDelegate;
	ScriptDelegate.BindUFunction(SubscriberClass, SubscriberFunctionName);
	DelegateEvent.Remove(ScriptDelegate);
}


