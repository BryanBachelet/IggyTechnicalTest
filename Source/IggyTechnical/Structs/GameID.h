#pragma once

#include "CoreMinimal.h"
#include "GameID.generated.h"

UENUM(BlueprintType)
enum class TypeID : uint8
{
	NONE =0,
	QUEST =1,
	ITEM = 2,
	NPC = 3,
};

USTRUCT(BlueprintType)
struct FGameID  
{
	GENERATED_BODY()
	
public:
	FGameID();
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TypeID IdType ;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int ID ;


	bool operator==(const FGameID& b) const;
	
	FString ToString() const;
};


