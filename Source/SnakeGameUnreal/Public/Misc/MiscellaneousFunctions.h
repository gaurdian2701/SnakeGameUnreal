#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MiscellaneousFunctions.generated.h"

UCLASS()
class SNAKEGAMEUNREAL_API UMiscellaneousFunctions : public UObject
{
	GENERATED_BODY()

public:
	UMiscellaneousFunctions(const FObjectInitializer& ObjectInitializer){}
	template<typename T>
	T GetHash(T Val1, T Val2)
	{
		return 32768 * Val1 + Val2;
	}
};
