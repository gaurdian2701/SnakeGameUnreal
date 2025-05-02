#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Core/DelegateData.h"
#include "SnakeGameState.generated.h"

UCLASS(Blueprintable)
class SNAKEGAMEUNREAL_API ASnakeGameState : public AGameState
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<UDelegateData> m_delegateData;
	virtual void BeginPlay() override;


public:
	ASnakeGameState();
	UFUNCTION(BlueprintCallable, Blueprintable, Category = "SnakeGameState")
	UDelegateData* GetDelegateData();
	void SubscribeToDelegate(FMulticastScriptDelegate& DelegateEvent, UObject* SubscriberClass, const FName& SubscriberFunctionName);
	void UnsubscribeFromDelegate(FMulticastScriptDelegate& DelegateEvent, UObject* SubscriberClass, const FName& SubscriberFunctionName); 
};


