#include "InteractComponent.h"

#include "IggyTechnical/IggyTechnicalGameMode.h"
#include "IggyTechnical/Quest/QuestManager.h"
#include "Kismet/GameplayStatics.h"

UInteractComponent::UInteractComponent()
{
	InteractText = TEXT("Interact ");
	PrimaryComponentTick.bRunOnAnyThread =false;
	
}

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();


	
}

void UInteractComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	Super::EndPlay(EndPlayReason);
	AIggyTechnicalGameMode* GameMode = Cast<AIggyTechnicalGameMode>( UGameplayStatics::GetGameMode(GetWorld()));
	AQuestManager* QuestManager =GameMode->QuestManager;

}



void UInteractComponent::BindQuestUpdateFunction()
{
	AIggyTechnicalGameMode* GameMode = Cast<AIggyTechnicalGameMode>( UGameplayStatics::GetGameMode(GetWorld()));
	if( GameMode->QuestManager == nullptr )
		GameMode->SpawnQuestManager();
	
	AQuestManager* QuestManager = GameMode->QuestManager;
	QuestManager->OnQuestStepChange.AddDynamic(this, &UInteractComponent::OnQuestUpdate);
}


void UInteractComponent::OnQuestUpdate(FGameID QuestID, FGameID InteractObjectID)
{

}



void UInteractComponent::Interact_Implementation()
{
	if(!bCanInteract)
		return;
}



void UInteractComponent::FinishInteract_Implementation()
{
}
