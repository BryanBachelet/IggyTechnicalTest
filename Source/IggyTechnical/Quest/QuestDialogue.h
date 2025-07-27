#pragma once

#include "CoreMinimal.h"
#include "QuestDialogue.generated.h"

#pragma region Quest Dialogue Struct
UENUM(BlueprintType)
enum class EQuestAnswerAction : uint8
{
	NONE = 0,
	QUIT = 1, // Quit the dialogue
	ACCEPT =2, // Accept the quest
	VALIDATE = 3, // Validate a quest's step
};

USTRUCT(BlueprintType)
struct FQuestDialogueAnswer 
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FString QuestAnswer;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int KeyNextDialogue;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	EQuestAnswerAction AnswerAction;
};

USTRUCT(BlueprintType)
struct FQuestDialogue 	
{
	GENERATED_USTRUCT_BODY()
	
	public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int KeyDialogue = 0;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly )
	FText dialogueLine;

	UPROPERTY(EditAnywhere,BlueprintReadOnly )
	TArray<FQuestDialogueAnswer> QuestAnswers;
	
};

#pragma endregion