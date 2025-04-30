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
	TObjectPtr<UDelegateData> GetDelegateData() const;
	UDelegateData::FOnAppleEaten& GetAppleEatenDelegate() const;
	UDelegateData::FOnPlayerDied& GetPlayerDiedDelegate() const;
	UFUNCTION(BlueprintCallable, Category = "Snake Game State Func")
	UDelegateData* GetDelegateData();
	void SubscribeToDelegate(FMulticastScriptDelegate& DelegateEvent, UObject* SubscriberClass, const FName& SubscriberFunctionName);
	void UnsubscribeFromDelegate(FMulticastScriptDelegate& DelegateEvent, UObject* SubscriberClass, const FName& SubscriberFunctionName); 
};


