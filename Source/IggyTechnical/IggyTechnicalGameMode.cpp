// Copyright Epic Games, Inc. All Rights Reserved.

#include "IggyTechnicalGameMode.h"
#include "Character/IggyTechnicalCharacter.h"
#include "Interaction/InteractComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AIggyTechnicalGameMode::AIggyTechnicalGameMode()
{

        	
}

void AIggyTechnicalGameMode::SpawnQuestManager()
{
	AActor* quest  = GetWorld()->SpawnActor(QuestType);
	QuestManager = Cast<AQuestManager>(quest);
}

void AIggyTechnicalGameMode::RegisterInteractiveComponents(UInteractComponent* QuestComponent)
{
	if(QuestManager->bIsInitialize)
	{
		QuestComponent->BindQuestUpdateFunction();
		return;
	}
	
	QuestComponentsArray.Add(QuestComponent);
}

void AIggyTechnicalGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AIggyTechnicalGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if(QuestManager == nullptr)
		SpawnQuestManager();
}
