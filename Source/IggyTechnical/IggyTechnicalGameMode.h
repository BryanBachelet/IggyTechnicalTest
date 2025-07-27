// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Quest/QuestManager.h"
#include "IggyTechnicalGameMode.generated.h"

class UInteractComponent;

UCLASS(minimalapi,Blueprintable)
class AIggyTechnicalGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AQuestManager* QuestManager;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AActor> QuestType;

	TArray<UInteractComponent*> QuestComponentsArray;
	
	AIggyTechnicalGameMode();

	void SpawnQuestManager();

	// Register Interactive Components for the Quest manager
	void RegisterInteractiveComponents(UInteractComponent* QuestComponent);
	
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
};



