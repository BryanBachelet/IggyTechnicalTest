#include "CollectComponent.h"

#include "IggyTechnical/IggyTechnicalGameMode.h"
#include "IggyTechnical/Character/CharacterQuestComponent.h"
#include "IggyTechnical/Character/IggyTechnicalCharacter.h"
#include "IggyTechnical/Structs/ObjectTableRow.h"
#include "Kismet/GameplayStatics.h"


class AIggyTechnicalGameMode;

UCollectComponent::UCollectComponent()
{
	HasBeenCollect =false;
	CanBeCollect=false;
	FeedbackMesh =nullptr;
	PrimaryComponentTick.bRunOnAnyThread =false;


	FItemRowData* data = ItemData.GetRow<FItemRowData>(ItemData.RowName.ToString());
	if(data != nullptr)
	{
		ItemName = data->Name.ToString();
		IdItem =  data->GameID;
	}

	
}

void UCollectComponent::SetFeedbackMesh(UStaticMeshComponent* mesh)
{
	FeedbackMesh = mesh;

}

bool UCollectComponent::CheckID(FGameID gameID)
{
	return  gameID == IdItem;
}

void UCollectComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InteractText = FString::Printf( TEXT("Collect %s ") , *ItemName);
	FeedbackMesh->SetHiddenInGame(true); 
	AIggyTechnicalGameMode* GameMode = Cast<AIggyTechnicalGameMode>( UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->RegisterInteractiveComponents(this);
}

void UCollectComponent::Interact_Implementation()
{
	Super::Interact_Implementation();

	if(!CanBeCollect || !bCanInteract ) return;
	
	ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	AIggyTechnicalCharacter* playerCharacter = Cast<AIggyTechnicalCharacter>(character);
	if (playerCharacter)
	{
		UCharacterQuestComponent* characterQuestComponent = playerCharacter->GetComponentByClass<UCharacterQuestComponent>();
		characterQuestComponent->CheckCollectStep(IdItem);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, 
											 FString::Printf(TEXT("Collect interaction working") ));
		}
		
		FinishInteract_Implementation();
	}
}

void UCollectComponent::FinishInteract_Implementation()
{
	Super::FinishInteract_Implementation();

	FeedbackMesh->SetHiddenInGame(true);
	CanBeCollect =false;
	HasBeenCollect =true;
	bCanInteract = false;
}



void UCollectComponent::OnQuestUpdate(FGameID QuestID,FGameID InteractObjectID)
{
	Super::OnQuestUpdate(QuestID,InteractObjectID);
	if(InteractObjectID == IdItem)
	{
		QuestIDRelated = QuestID;
		CanBeCollect =true;
		FeedbackMesh->SetHiddenInGame(false);
		bCanInteract =true;
		return;
	}

	if(InteractObjectID != IdItem && QuestIDRelated == QuestID)
	{
		FeedbackMesh->SetHiddenInGame(true);
		QuestIDRelated = QuestID;
		CanBeCollect =false;
		bCanInteract =false;
	}
}

#if  WITH_EDITOR
void UCollectComponent::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
		
	if (PropertyChangedEvent.GetPropertyName() == TEXT("RowName"))
	{
		FItemRowData* data = ItemData.GetRow<FItemRowData>(ItemData.RowName.ToString());
		ItemName = data->Name.ToString();
		IdItem =  data->GameID;
	}
}
#endif
