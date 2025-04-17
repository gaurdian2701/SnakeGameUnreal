#pragma once
#include "CoreMinimal.h"
#include "UAppleSpawner.h"
#include "UObject/Object.h"
#include "Spawning_World_Subsystem.generated.h"

UCLASS()
class SNAKEGAMEUNREAL_API USpawning_World_Subsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UPROPERTY()
	TObjectPtr<UAppleSpawner> m_appleSpawner = nullptr;
};
