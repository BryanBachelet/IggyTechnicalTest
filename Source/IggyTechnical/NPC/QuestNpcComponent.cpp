#include "QuestNpcComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameModeBase.h"
#include "IggyTechnical/IggyTechnicalGameMode.h"
#include "IggyTechnical/Character/CharacterQuestComponent.h"
#include "IggyTechnical/Character/IggyTechnicalCharacter.h"
#include "IggyTechnical/Structs/ObjectTableRow.h"
#include "Kismet/GameplayStatics.h"

UQuestNpcComponent::UQuestNpcComponent()
{

	FNpcRowData* data = NPCData.GetRow<FNpcRowData>(NPCData.RowName.ToString());
	if(data)
	{
		QuestNpcName =  data->Name.ToString();
		NpcID =  data->GameID;
	}
	
}

void UQuestNpcComponent::BeginPlay()
{
	Super::BeginPlay();

	InteractText = FString::Printf( TEXT("Talk to %s ") , *QuestNpcName);
	if(QuestMeshFeedback)
	{
		if( bHasQuestToGive && IsQuestTake )
		{
			QuestMeshFeedback->SetHiddenInGame(false);
			bCanInteract =true;
		}
		else 
		{
			QuestMeshFeedback->SetHiddenInGame(true);
			bCanInteract= false;
		}
	}

	AIggyTechnicalGameMode* GameMode = Cast<AIggyTechnicalGameMode>( UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->RegisterInteractiveComponents(this);	
}

void UQuestNpcComponent::OnQuestUpdate(FGameID QuestID, FGameID InteractObjectID)
{
	Super::OnQuestUpdate(QuestID, InteractObjectID);

	if(  InteractObjectID == NpcID)
	{
		QuestIDRelated = QuestID;
		QuestMeshFeedback->SetHiddenInGame(false);
		bCanInteract =true; 
		return; 
	}

	if(IsQuestTake && QuestIDRelated == QuestID && InteractObjectID != NpcID)
	{
		QuestMeshFeedback->SetHiddenInGame(true);
		bCanInteract =false;
	}
	
}

void UQuestNpcComponent::FinishInteract_Implementation()
{
	Super::FinishInteract_Implementation();
	if(InteractState == EInteractState::TALK)
	{
		UGameplayStatics::GetPlayerController(GetWorld(),0)->SetIgnoreMoveInput(false);
		
	}
	
	AIggyTechnicalCharacter* character = Cast<AIggyTechnicalCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	UCharacterQuestComponent* characterQuestComponent =	Cast<UCharacterQuestComponent>(character->GetComponentByClass<UCharacterQuestComponent>());
	if(!IsQuestTake && characterQuestComponent->HasAlreadyQuest(QuestIDGive))
	{
		IsQuestTake =true;
		QuestMeshFeedback->SetHiddenInGame(true);
	}
}

void UQuestNpcComponent::Interact_Implementation()
{
	Super::Interact_Implementation();

	
	if(InteractState == EInteractState::TALK && bCanInteract)
	{
		// Need to disable player movement
		ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
		AIggyTechnicalCharacter* playerCharacter = Cast<AIggyTechnicalCharacter>(character);
		playerCharacter->GetCharacterMovement()->Velocity = FVector(0, 0, 0);

		UGameplayStatics::GetPlayerController(GetWorld(),0)->SetIgnoreMoveInput(true);
	}
}

bool UQuestNpcComponent::CheckInteractionValid()
{
	if(InteractState !=  EInteractState::TALK) return false;

	if( bHasQuestToGive && !IsQuestTake  ) return true;
	
	ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	AIggyTechnicalCharacter* playerCharacter = Cast<AIggyTechnicalCharacter>(character);
	UCharacterQuestComponent* QuestPlayerComponent = playerCharacter->GetComponentByClass<UCharacterQuestComponent>();

	if(QuestPlayerComponent->IsValidNPC(QuestNpcName))
		return true;
	else
		return false;
}

#if WITH_EDITOR
void UQuestNpcComponent::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	
	if (PropertyChangedEvent.GetPropertyName() == TEXT("RowName"))
	{
		
		FNpcRowData* data = NPCData.GetRow<FNpcRowData>(NPCData.RowName.ToString());
		QuestNpcName =  data->Name.ToString();
		NpcID =  data->GameID;
	}
}
#endif


