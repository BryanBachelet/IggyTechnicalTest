#pragma once
#include "CoreMinimal.h"
#include "QuestStep.h"
#include "QuestDialogue.h"
#include "IggyTechnical/Structs/GameID.h"
#include "QuestData.generated.h"



#pragma region Quest Step Struct
struct FGameID;

UENUM(BlueprintType)
enum class EQuestStepEnum : uint8 // Type of action ask for the quest
{
	NONE = 0,
	TALK = 1,
	GO = 2 ,
	COLLECT = 3,
	
};

UCLASS(Blueprintable,EditInlineNew)
class IGGYTECHNICAL_API UQuestStep  : public  UObject// Data a step of a quest
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int ID = 0;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FText Description ;

	UPROPERTY(EditAnywhere,BlueprintReadOnly);
	EQuestStepEnum TypeStep = EQuestStepEnum::NONE;
	
	UPROPERTY(Instanced,EditAnywhere,BlueprintReadOnly)
	UStepDetails*  Details;
	
	UQuestStep();
	virtual ~UQuestStep() override;
	
	UQuestStep* CopyStruct();
};

inline UQuestStep* UQuestStep::CopyStruct()
{
	
	UQuestStep*  copy = DuplicateObject(this,NULL);
	return copy ;
}


#pragma endregion


UCLASS()
class UQuestData :public  UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName QuestName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite )
	FText QuestDescription;

	UPROPERTY(EditAnywhere,BlueprintReadWrite )
	FGameID QuestID;
	
	UQuestData();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Instanced,CallInEditor)
	TArray<UQuestStep*> QuestSteps;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite )
	TArray<FQuestDialogue> QuestDialogueArray;


};
