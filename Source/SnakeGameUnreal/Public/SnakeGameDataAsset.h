#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SnakeGameDataAsset.generated.h"

class AApple;

USTRUCT(BlueprintType)
struct FRoomData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Floor Length(X)")
	float m_roomLength = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Floor Width(Y)")
	float m_roomWidth = 0.0f;
};

UCLASS()
class SNAKEGAMEUNREAL_API USnakeGameDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Apple Blueprint")
	TSubclassOf<AApple> AppleBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wall Blueprint")
	TSubclassOf<AActor> m_wallBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Floor Static Mesh")
	TObjectPtr<UStaticMesh> m_floorStaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Floor Mesh Offset")
	float m_floorMeshOffset = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level Room Data")
	TArray<FRoomData> RoomData;
};
