#include "QuestItemActor.h"

#include "QuestManager.h"
#include "IggyTechnical/IggyTechnicalGameMode.h"
#include "IggyTechnical/Interaction/CollectComponent.h"
#include "Kismet/GameplayStatics.h"



AQuestItemActor::AQuestItemActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	
	MeshQuestFeedback = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Quest Feedback");
	MeshQuestFeedback->AttachToComponent(Mesh,FAttachmentTransformRules::KeepRelativeTransform);
	
	CollectInteractionComponent = CreateDefaultSubobject<UCollectComponent>("Collect Component");
	CollectInteractionComponent->SetFeedbackMesh(MeshQuestFeedback);
	
}

void AQuestItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}


