#pragma once
#include "CoreMinimal.h"
#include "ABodySegmentBase.h"
#include "Engine/DataAsset.h"
#include "SnakeGameDataAsset.generated.h"

class AApple;

USTRUCT(BlueprintType)
struct FRoomData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room Length(X)")
	int m_roomLength = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room Width(Y)")
	int m_roomWidth = 0;
};

UCLASS()
class SNAKEGAMEUNREAL_API USnakeGameDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Snake Body Blueprint")
	TSubclassOf<ABodySegmentBase> m_SnakeSegment;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Apple Blueprint")
	TSubclassOf<AApple> m_AppleBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wall Blueprint")
	TSubclassOf<AActor> m_WallBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Floor Static Mesh")
	TObjectPtr<UStaticMesh> m_FloorStaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Floor Mesh Offset")
	float m_FloorMeshOffset = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level Room Data")
	TArray<FRoomData> m_RoomData;
};
