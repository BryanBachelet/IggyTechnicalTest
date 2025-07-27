#include "QuestManager.h"

#include "Elements/Columns/TypedElementAlertColumns.h"
#include "GameFramework/Character.h"
#include "IggyTechnical/IggyTechnicalGameMode.h"
#include "IggyTechnical/Character/CharacterQuestComponent.h"
#include "IggyTechnical/Interaction/InteractComponent.h"
#include "Kismet/GameplayStatics.h"

AQuestManager::AQuestManager()
{
	bIsInitialize = false;
}

void AQuestManager::BeginPlay()
{
	Super::BeginPlay();
	CharacterQuestComponent = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetComponentByClass<
		UCharacterQuestComponent>();

	AIggyTechnicalGameMode* GameMode = Cast<AIggyTechnicalGameMode>( UGameplayStatics::GetGameMode(GetWorld()));
	SubscribeInteractiveComponents(GameMode->QuestComponentsArray);
	GameMode->QuestComponentsArray.Reset();
	
	bIsInitialize =true;
 
}

void AQuestManager::SubscribeInteractiveComponents(TArray<UInteractComponent*> InteractComponentArray)
{
	for (UInteractComponent* DataArray : InteractComponentArray)
	{
		DataArray->BindQuestUpdateFunction();
	}
}

void AQuestManager::SendPlayerQuestData(FGameID questID)
{
	UQuestData* targetQuestData = GetQuestData(questID);
	
	//Check if the quest exist
	if (targetQuestData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Quest Data id %s doesn't exist"), *questID.ToString());
		return;
	}

	//Check if the player has already the quest
	if (CharacterQuestComponent->HasAlreadyQuest(questID))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player has already this quest %s "), *questID.ToString());
		return;
	}

	// Send the quest to the character quest components
	UCharacterQuestData* characterQuestData = CreateCharacterQuestData(targetQuestData);
	CharacterQuestComponent->SendNewQuest(characterQuestData);
}

FString AQuestManager::GetStepDescription(UQuestData* data, int currentStepIndex)
{
	EQuestStepEnum currentTypeStep = data->QuestSteps[currentStepIndex]->TypeStep;

	if (!CharacterQuestComponent->HasAlreadyQuest(data->QuestID))
	{
		return TEXT("Wrong Quest  ID");
	}
	UCharacterQuestData* QuestData  = CharacterQuestComponent->GetQuestData(data->QuestID);
	
	FString description;
	switch (currentTypeStep)
	{
	case EQuestStepEnum::GO:
		{
			UQuestDestinationDetails* destinationDetails = Cast<UQuestDestinationDetails>(QuestData->QuestStep[currentStepIndex]->Details);
			if (destinationDetails == nullptr)
			{
				 UE_LOG(LogTemp, Warning, TEXT("Quest destination details is null for quest id %s "), *data->QuestName.ToString());
				description = TEXT("Quest destination details is null");
			}
			else
			{
				 description = FString::Printf(TEXT("Go to %s"), *destinationDetails->NamePlaceText);
			}
		}
	break;

	case EQuestStepEnum::COLLECT:
		{
			UQuestCollectDetails* collectDetails = Cast<UQuestCollectDetails>(
				QuestData->QuestStep[currentStepIndex]->Details);
			if (collectDetails == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Quest collect details is null for quest id %s  "), *data->QuestName.ToString());
				description = TEXT("Quest collect details is null");
			}
			else
			{
				description = FString::Printf(TEXT("Collect to %i / %i "),collectDetails->CurrentCollect,collectDetails->NumberToCollect);
			}
		}
		break;
	case EQuestStepEnum::TALK:
		{
			UQuestTalkDetails* talkDetails = Cast<UQuestTalkDetails>(QuestData->QuestStep[currentStepIndex]->Details);
			if (talkDetails == nullptr)
			{
				 UE_LOG(LogTemp, Warning, TEXT("Quest talk details is null for quest id %s "), *data->QuestName.ToString());
				description = TEXT("Quest talk details is null");
			}
			else
			{
				 description = FString::Printf(TEXT("Talk to %s"),*talkDetails->NameNPC);
			}
		}
		break;
	default
	:
		description = TEXT("Quest destination not valid ");
		break;
	}

	return description;
}

UQuestData* AQuestManager::GetQuestData(FGameID id)
{
	for (int i = 0; i < QuestDataArray.Num(); i++ )
	{
		if(QuestDataArray[i]->QuestID == id)
			return QuestDataArray[i];
	}
	return  nullptr;
}

void AQuestManager::UpdateQuestStep(FGameID QuestID, const UQuestStep* QuestStep) const
{

	// Condition trigger when the quest is finish
	if(QuestStep ==	nullptr)
	{
		FGameID defaultID;
		defaultID.IdType = TypeID::NONE;
		OnQuestStepChange.Broadcast(QuestID, defaultID);
		return;
	}
	
	switch (QuestStep->TypeStep)
	{
	case EQuestStepEnum::TALK:
		{
			UQuestTalkDetails* talkDetails = Cast<UQuestTalkDetails>(
			   QuestStep->Details);
			OnQuestStepChange.Broadcast(QuestID,talkDetails->IdNpc);
			return;
		}
	break;
			
	case EQuestStepEnum::COLLECT:
		{
			UQuestCollectDetails* collectDetails = Cast<UQuestCollectDetails>(
			QuestStep->Details);
			OnQuestStepChange.Broadcast(QuestID,collectDetails->IdItem);
			return;
		}
		break;
	default:
		{
			FGameID defaultID;
			defaultID.IdType = TypeID::NONE;
			OnQuestStepChange.Broadcast(QuestID,defaultID);
			return;
		}
		break;
	}
}

UCharacterQuestData* AQuestManager::CreateCharacterQuestData(const UQuestData* QuestData)
{
	UCharacterQuestData* characterQuestData = NewObject<UCharacterQuestData>();
	characterQuestData->QuestId = QuestData->QuestID;
	characterQuestData->QuestName = QuestData->QuestName.ToString();
	characterQuestData->QuestDescription = QuestData->QuestDescription.ToString();
	characterQuestData->QuestStep = QuestData->QuestSteps;

	for(int i = 0; i < characterQuestData->QuestStep.Num(); i++ )
	{
		characterQuestData->QuestStep[i]  =characterQuestData->QuestStep[i]->CopyStruct();
	}
	return characterQuestData;
}
