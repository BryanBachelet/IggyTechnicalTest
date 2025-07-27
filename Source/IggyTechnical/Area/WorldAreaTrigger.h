#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "WorldAreaTrigger.generated.h"


UENUM(BlueprintType)
enum class EWorldPlace : uint8 // Place in the world
{
	NONE = 0,
	TOWN = 1,
	FOREST = 2 ,
	
};


UCLASS(config=Game, Blueprintable)
class AWorldAreaTrigger : public ATriggerBox
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	EWorldPlace WorldPlace = EWorldPlace::TOWN;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	FText WorldPlaceName ;

	
public:
	AWorldAreaTrigger();

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, class AActor* OtherActor);
	
	
};
