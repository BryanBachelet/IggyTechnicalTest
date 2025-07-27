#pragma once

#include "CoreMinimal.h"
#include "IggyTechnical/Interaction/InteractComponent.h"
#include "IggyTechnical/Structs/GameID.h"
#include "QuestNpcComponent.generated.h"

UCLASS(Blueprintable)
class UQuestNpcComponent : public UInteractComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FDataTableRowHandle NPCData;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	FGameID QuestIDGive;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	FString QuestNpcName;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	FGameID NpcID;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	bool bHasQuestToGive;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	bool IsQuestTake;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	bool IsQuestValidate;
	
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* QuestMeshFeedback = nullptr;

	
	UQuestNpcComponent();

	virtual void BeginPlay() override;

	virtual void OnQuestUpdate(FGameID QuestID, FGameID InteractObjectID) override;
	virtual  void FinishInteract_Implementation() override;
	virtual  void Interact_Implementation() override;

	UFUNCTION(BlueprintCallable)
	bool CheckInteractionValid();

#if WITH_EDITOR
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif
};
