#include "QuestStep.h"

#include "IggyTechnical/Structs/ObjectTableRow.h"


UStepDetails::UStepDetails()
{
}

UQuestCollectDetails::UQuestCollectDetails()
{
}
#if WITH_EDITOR
void UQuestCollectDetails::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	
	if (PropertyChangedEvent.GetPropertyName() == TEXT("RowName"))
	{
		FItemRowData* data = ItemData.GetRow<FItemRowData>(ItemData.RowName.ToString());
		ItemName =  data->Name;
		IdItem =  data->GameID;
	}
}
#endif
UQuestTalkDetails::UQuestTalkDetails()
{
}
#if WITH_EDITOR
void UQuestTalkDetails::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName() == TEXT("RowName"))
	{
		FNpcRowData* data = NPCData.GetRow<FNpcRowData>(NPCData.RowName.ToString());
		NameNPC =  data->Name.ToString();
		IdNpc =  data->GameID;
	}
}
#endif
UQuestDestinationDetails::UQuestDestinationDetails()
{
	
}
