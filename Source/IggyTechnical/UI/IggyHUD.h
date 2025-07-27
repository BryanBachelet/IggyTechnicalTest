#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IggyHUD.generated.h"

class UPopupManagerComponent;

UCLASS(config=Game)
class AIggyHUD : public AHUD
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
	UPopupManagerComponent* PopupManager;
public:
	AIggyHUD();

	
	
	UFUNCTION(BlueprintCallable)
	UPopupManagerComponent* GetPopupManager();
};
