#include "CharacterQuestComponent.h"
#include "IggyTechnicalCharacter.h"
#include "IggyTechnical/IggyTechnicalGameMode.h"
#include "IggyTechnical/UI/IggyHUD.h"
#include "IggyTechnical/UI/PopupManagerComponent.h"
#include "Kismet/GameplayStatics.h"

UCharacterQuestComponent::UCharacterQuestComponent()
{
	OwnerActor = Cast<AIggyTechnicalCharacter>(GetOwner());
	bWantsInitializeComponent = true;
}

UCharacterQuestComponent::~UCharacterQuestComponent()
{
}

void UCharacterQuestComponent::InitializeComponent()
{
	Super::InitializeComponent();
	OwnerActor = Cast<AIggyTechnicalCharacter>(GetOwner());
}

void UCharacterQuestComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerActor->OnLocationChange.BindDynamic(this, &UCharacterQuestComponent::CheckLocationStep);
}

void UCharacterQuestComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	OwnerActor->OnLocationChange.Unbind();
}

void UCharacterQuestComponent::SendNewQuest(UCharacterQuestData* QuestData)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow,
	                                 FString::Printf(TEXT("Quest Data %s"), *QuestData->QuestName));

	AHUD* HUD = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD();
	AIggyHUD* IggyHUD = Cast<AIggyHUD>(HUD);
	
	FPopupData PopupData = FPopupData();
	PopupData.Text = TEXT("Quest accepted");
	PopupData.DurationPopup = 3.0f;
	IggyHUD->GetPopupManager()->AddPopupToQueue(PopupData);

	QuestDataArray.Add(QuestData);
	OwnerActor->AddQuest(QuestData);
	OwnerActor->UpdateQuest(QuestData);
	
	AIggyTechnicalGameMode* Iggy  = Cast<AIggyTechnicalGameMode>( UGameplayStatics::GetGameMode(GetWorld()));
	Iggy->QuestManager->UpdateQuestStep(QuestData->QuestId,QuestData->QuestStep[QuestData->CurrentStep]);
}

void UCharacterQuestComponent::ChangeQuestStep(FGameID IdSearch)
{
	UCharacterQuestData* questData = GetQuestData(IdSearch);
	questData->CurrentStep++;

	AIggyTechnicalGameMode* Iggy  = Cast<AIggyTechnicalGameMode>( UGameplayStatics::GetGameMode(GetWorld()));

	if (questData->QuestStep.Num() == questData->CurrentStep)
	{
		OwnerActor->FinishQuest(IdSearch);
		Iggy->QuestManager->UpdateQuestStep(questData->QuestId,nullptr);
		QuestDataArray.Remove(questData);
	}
	else
	{
		OwnerActor->UpdateQuest(questData);
		Iggy->QuestManager->UpdateQuestStep(questData->QuestId,questData->QuestStep[questData->CurrentStep]);
	}
}

UCharacterQuestData* UCharacterQuestComponent::GetQuestData(FGameID IdSearch)
{
	for (int i = 0; i < QuestDataArray.Num(); i++)
	{
		if (QuestDataArray[i]->QuestId == IdSearch)
			return QuestDataArray[i];
	}

	return nullptr;
}


bool UCharacterQuestComponent::HasAlreadyQuest(FGameID QuestId)
{
	for (int i = 0; i < QuestDataArray.Num(); i++)
	{
		if (QuestDataArray[i]->QuestId == QuestId) return true;
	}

	return false;
}

bool UCharacterQuestComponent::IsValidNPC(FString NpcName)
{
	for (int i = 0; i < QuestDataArray.Num(); i++)
	{
		int currentStep = QuestDataArray[i]->CurrentStep;
		if (QuestDataArray[i]->QuestStep[currentStep]->TypeStep == EQuestStepEnum::TALK)
		{
			UQuestTalkDetails* currentDetails = Cast<UQuestTalkDetails>(
				QuestDataArray[i]->QuestStep[currentStep]->Details);
			bool isValidName = currentDetails->NameNPC == NpcName;
			if (isValidName) return true;
		}
	}

	return false;
}

TArray<FQuestDialogue> UCharacterQuestComponent::GetStepDialogues(FGameID QuestId)
{
	UCharacterQuestData* questData = GetQuestData(QuestId);

	if (questData->QuestStep[questData->CurrentStep]->TypeStep == EQuestStepEnum::TALK)
	{
		UQuestTalkDetails* currentDetails = Cast<UQuestTalkDetails>(
			questData->QuestStep[questData->CurrentStep]->Details);
		return currentDetails->TalksDialogue;
	}
	return TArray<FQuestDialogue>();
}

void UCharacterQuestComponent::CheckLocationStep(EWorldPlace currentPlace)
{
	for (int i = 0; i < QuestDataArray.Num(); i++)
	{
		int currentStep = QuestDataArray[i]->CurrentStep;
		if (QuestDataArray[i]->QuestStep[currentStep]->TypeStep == EQuestStepEnum::GO)
		{
			UQuestDestinationDetails* Details = Cast<UQuestDestinationDetails>(
				QuestDataArray[i]->QuestStep[currentStep]->Details);
			bool isValidStep = Details->PlaceToGo == currentPlace;
			if (isValidStep)
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,
					                                 FString::Printf(TEXT("Quest Step %d is valid"), currentStep));
				}

				ChangeQuestStep(QuestDataArray[i]->QuestId);
			}
		}
	}
}

void UCharacterQuestComponent::CheckCollectStep(FGameID collectIdObject)
{
	for (int i = 0; i < QuestDataArray.Num(); i++)
	{
		int currentStep = QuestDataArray[i]->CurrentStep;
		if (QuestDataArray[i]->QuestStep[currentStep]->TypeStep == EQuestStepEnum::COLLECT)
		{
			UQuestCollectDetails* collectDetails = Cast<UQuestCollectDetails>(
				QuestDataArray[i]->QuestStep[currentStep]->Details);

			if (collectDetails->IdItem == collectIdObject)
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,
					                                 FString::Printf(
						                                 TEXT("Quest Collect Step %d is valid"), currentStep));
				}
				collectDetails->CurrentCollect++;
				OwnerActor->UpdateQuest(QuestDataArray[i]);
				if (collectDetails->CurrentCollect >= collectDetails->NumberToCollect)
				{
					ChangeQuestStep(QuestDataArray[i]->QuestId);
				}
			}
		}
	}
}

