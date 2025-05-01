#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PersistentData_Instance_Subsystem.generated.h"

class USnakeGameDataAsset;

UCLASS()
class SNAKEGAMEUNREAL_API UPersistentData_Instance_Subsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Persistent Data Instance Subsystem")
	USnakeGameDataAsset* GetGameData() const;

	void SetGameData(const TObjectPtr<USnakeGameDataAsset> GameData);
	
	UPROPERTY()
	TObjectPtr<USnakeGameDataAsset> m_GameData = nullptr;
};
