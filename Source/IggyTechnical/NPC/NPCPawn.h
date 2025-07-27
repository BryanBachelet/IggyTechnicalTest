#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "NPCPawn.generated.h"

class UQuestNpcComponent;

UCLASS(config=Game)
class ANPCPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(Category=NPC, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	
	UPROPERTY(Category=NPC, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(Category=NPC, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> MeshFeedbackQuest;

		
public:
	ANPCPawn();
	

	virtual void BeginPlay() override;
};
