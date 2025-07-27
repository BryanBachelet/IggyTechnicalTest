#include "NPCPawn.h"

#include "QuestNpcComponent.h"

ANPCPawn::ANPCPawn()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->InitCapsuleSize(34.0f, 88.0f);
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	CapsuleComponent->CanCharacterStepUpOn = ECB_No;
	CapsuleComponent->SetShouldUpdatePhysicsVolume(true);
	CapsuleComponent->SetCanEverAffectNavigation(false);
	CapsuleComponent->bDynamicObstacle = true;
	RootComponent = CapsuleComponent;


	
	MeshFeedbackQuest =  CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Feedback Quest"));
	if(MeshFeedbackQuest)
	{
		MeshFeedbackQuest->AlwaysLoadOnClient = true;
		MeshFeedbackQuest->AlwaysLoadOnServer = true;
		MeshFeedbackQuest->bOwnerNoSee = true;
		MeshFeedbackQuest->bCastDynamicShadow = true;
		MeshFeedbackQuest->bAffectDynamicIndirectLighting = true;
		MeshFeedbackQuest->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		MeshFeedbackQuest->AttachToComponent(CapsuleComponent,FAttachmentTransformRules::KeepRelativeTransform);
		static FName MeshCollisionProfileName(TEXT("CharacterMesh"));
		MeshFeedbackQuest->SetCollisionProfileName(MeshCollisionProfileName);
		MeshFeedbackQuest->SetGenerateOverlapEvents(false);
		MeshFeedbackQuest->SetCanEverAffectNavigation(false);
	}

	
	Mesh = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	if (Mesh)
	{
		Mesh->AlwaysLoadOnClient = true;
		Mesh->AlwaysLoadOnServer = true;
		Mesh->bOwnerNoSee = false;
		Mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
		Mesh->bCastDynamicShadow = true;
		Mesh->bAffectDynamicIndirectLighting = true;
		Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Mesh->SetupAttachment(CapsuleComponent);
		static FName MeshCollisionProfileName(TEXT("CharacterMesh"));
		Mesh->SetCollisionProfileName(MeshCollisionProfileName);
		Mesh->SetGenerateOverlapEvents(false);
		Mesh->SetCanEverAffectNavigation(false);
	}

	
}

void ANPCPawn::BeginPlay()
{
	Super::BeginPlay();

	
}
