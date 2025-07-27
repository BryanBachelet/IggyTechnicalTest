#include "WorldAreaTrigger.h"

#include "IggyTechnical/Character/IggyTechnicalCharacter.h"

AWorldAreaTrigger::AWorldAreaTrigger()
{
		
	WorldPlaceName = FText::FromString(TEXT("Empty Location"));
	OnActorBeginOverlap.AddDynamic(this,&AWorldAreaTrigger::OnOverlapBegin);
}

void AWorldAreaTrigger::OnOverlapBegin(AActor* OverlappedActor, class AActor* OtherActor)
{
	AIggyTechnicalCharacter* playerCharacter = Cast<AIggyTechnicalCharacter>(OtherActor);
	if(playerCharacter != nullptr)
	{
		// Change Location Player
		playerCharacter->ChangeLocation(WorldPlace,WorldPlaceName);
	}
}
