#pragma once

#include "CoreMinimal.h"
#include "GameID.h"
#include "ObjectTableRow.generated.h"

USTRUCT(BlueprintType)
struct FNpcRowData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameID GameID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	
};

USTRUCT(BlueprintType)
struct FItemRowData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameID GameID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	
};

