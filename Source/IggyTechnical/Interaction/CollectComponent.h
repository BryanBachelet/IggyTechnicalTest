#pragma once


#include "InteractComponent.h"
#include "IggyTechnical/Structs/GameID.h"
#include "CollectComponent.generated.h"


UCLASS()
class UCollectComponent : public UInteractComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FDataTableRowHandle ItemData;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	bool HasBeenCollect;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	bool CanBeCollect;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	FGameID IdItem;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	FString ItemName;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* FeedbackMesh;
	
public:

	UCollectComponent();

	void SetFeedbackMesh(UStaticMeshComponent* mesh);

	bool CheckID(FGameID gameID);
	
	virtual void BeginPlay() override;
	virtual  void Interact_Implementation() override;
	virtual  void FinishInteract_Implementation() override;
	
	virtual void OnQuestUpdate(FGameID QuestID, FGameID InteractObjectID) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
};
