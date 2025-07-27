#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IggyTechnical/Structs/GameID.h"
#include "QuestItemActor.generated.h"
class UCollectComponent;

UCLASS(config=Game, Blueprintable)
class AQuestItemActor : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(AllowPrivateAccess=true), Category="General")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true), category="QuestItem")
	UCollectComponent* CollectInteractionComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(AllowPrivateAccess=true), Category="QuestItem")
	UStaticMeshComponent* MeshQuestFeedback;
	
public:
	AQuestItemActor();

	virtual void BeginPlay() override;
};
