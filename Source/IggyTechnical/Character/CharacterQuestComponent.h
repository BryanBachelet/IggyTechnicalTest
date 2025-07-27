#pragma once

#include "CoreMinimal.h"

#include  "../Quest/QuestData.h"
#include "CharacterQuestComponent.generated.h"


class AIggyTechnicalCharacter;

// Data struct for character quest data
UCLASS(BlueprintType)
class UCharacterQuestData : public  UObject
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameID QuestId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentStep = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UQuestStep*> QuestStep;
};


UCLASS()
class UCharacterQuestComponent : public UActorComponent 
{
	GENERATED_BODY()
private:
	
	UPROPERTY()
	TArray<UCharacterQuestData*> QuestDataArray;
	
	UPROPERTY()
	AIggyTechnicalCharacter* OwnerActor;
	
public:
	
	UCharacterQuestComponent();
	~UCharacterQuestComponent();

	virtual  void InitializeComponent() override;
	virtual void BeginPlay() override;
	virtual  void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION()
	void SendNewQuest( UCharacterQuestData* QuestData);

	UFUNCTION(BlueprintCallable)
	void ChangeQuestStep(FGameID IdSearch);

	UFUNCTION(BlueprintCallable)
	UCharacterQuestData* GetQuestData(FGameID IdSearch);
	
	bool HasAlreadyQuest(FGameID QuestId);

	bool IsValidNPC(FString NpcName);

	UFUNCTION(BlueprintCallable)
	TArray<FQuestDialogue> GetStepDialogues(FGameID QuestId);
	

	UFUNCTION()
	void CheckLocationStep(EWorldPlace currentPlace);
	void CheckCollectStep(FGameID collectIdObject);

	

	

	
	
};
