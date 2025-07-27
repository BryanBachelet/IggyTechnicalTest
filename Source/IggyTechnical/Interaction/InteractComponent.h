#pragma once

#include "CoreMinimal.h"
#include "IggyTechnical/Structs/GameID.h"
#include "InteractComponent.generated.h"

struct FGameID;

UENUM(BlueprintType)
enum class EInteractState : uint8
{
	NONE = 0,
	TALK = 1,
	COLLECT = 2,
	KILL = 3,
};


DECLARE_DELEGATE_OneParam(FOnInteractFinished,EInteractState);
DECLARE_DELEGATE_OneParam(FOnInteractStarted,EInteractState);
DECLARE_DELEGATE_OneParam(FOnInteractCancel,EInteractState);

UCLASS()
class UInteractComponent : public  UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere);
	FGameID QuestIDRelated ;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true));
	bool bCanInteract;

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EInteractState InteractState;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString InteractText;

	FOnInteractCancel OnInteractCancelDelegate;
	FOnInteractStarted OnInteractStartedDelegate;
	FOnInteractFinished OnInteractFinishedDelegate;

	UInteractComponent();

	virtual void BeginPlay() override;
	virtual  void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	void BindQuestUpdateFunction();
	
	UFUNCTION()
	virtual  void OnQuestUpdate(FGameID QuestID, FGameID InteractObjectID);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact();

	virtual  void  Interact_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	 void FinishInteract(); 

	virtual  void FinishInteract_Implementation();
};
