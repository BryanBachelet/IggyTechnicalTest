#pragma once

#include "CoreMinimal.h"	
#include "QuestData.h"
#include "QuestManager.generated.h"

class UInteractComponent;
class UCharacterQuestData;
class UCharacterQuestComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnQuestStepChanged, FGameID,QuestID,FGameID, ObjectID );


UCLASS(config=Game)
class AQuestManager : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UCharacterQuestComponent* CharacterQuestComponent;
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInitialize =false;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<UQuestData*> QuestDataArray;
	
	FOnQuestStepChanged OnQuestStepChange;
	
	AQuestManager();
	
	virtual void BeginPlay() override;

	// Subscribe interactive component to OnQuestStepChange 
	void SubscribeInteractiveComponents(TArray<UInteractComponent*> QuestDataArray);
	
	UFUNCTION(BlueprintCallable)
	void SendPlayerQuestData(FGameID questID);


	// Give the quest description depending on the action to do 
	UFUNCTION(BlueprintCallable)
	FString GetStepDescription(UQuestData* data,int currentStepIndex);
	
	UFUNCTION(BlueprintCallable)
	UQuestData* GetQuestData(FGameID Id);

	// Inform interactive object that quest has change of state
	void UpdateQuestStep(FGameID QuestID, const UQuestStep* QuestStep) const;
		
private:
	static UCharacterQuestData* CreateCharacterQuestData( const UQuestData* QuestData);

	
};
