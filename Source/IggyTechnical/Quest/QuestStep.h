#pragma once

#include "CoreMinimal.h"
#include "QuestDialogue.h"
#include "IggyTechnical/Area/WorldAreaTrigger.h"
#include "IggyTechnical/Structs/GameID.h"
#include "QuestStep.generated.h"
enum class EWorldPlace : uint8;

UCLASS(EditInlineNew,BlueprintType)
class UStepDetails: public UObject
{
	GENERATED_BODY()

public:
	UStepDetails();
};

UCLASS(Blueprintable)
class UQuestCollectDetails : public UStepDetails
{
	GENERATED_BODY()

public:
	UQuestCollectDetails();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDataTableRowHandle ItemData;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int NumberToCollect = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int CurrentCollect = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ItemName ;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameID IdItem ;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
};

UCLASS(Blueprintable)
class UQuestTalkDetails : public UStepDetails
{
	GENERATED_BODY()

public:
	UQuestTalkDetails();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDataTableRowHandle NPCData;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString NameNPC = "";
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameID IdNpc ;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FQuestDialogue> TalksDialogue;
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
};

UCLASS(Blueprintable)
class UQuestDestinationDetails : public UStepDetails
{
	GENERATED_BODY()

public:
	UQuestDestinationDetails();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWorldPlace PlaceToGo = EWorldPlace::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString NamePlaceText;
};
