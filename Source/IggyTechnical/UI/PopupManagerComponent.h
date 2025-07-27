#pragma once

#include "CoreMinimal.h"
#include "Containers/Queue.h"
#include "PopupManagerComponent.generated.h"

USTRUCT(BlueprintType)
struct FPopupData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DurationPopup;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLaunchPopup, FPopupData, PopupData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndPopup, FPopupData, PopupData);

UCLASS(Blueprintable, BlueprintType)
class UPopupManagerComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY()
	float PopupTimer = 0;
	UPROPERTY()
	bool bIsPopupShow = false;

	bool bIsPopupStartToFadeOut = false;

	TQueue<FPopupData> PopupQueue;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPopupData CurrentPopupData;
	
	UPopupManagerComponent();

	

	UFUNCTION(BlueprintCallable)
	void AddPopupToQueue(FPopupData PopupData);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FOnLaunchPopup OnLaunchPopup;
	
	UPROPERTY(BlueprintAssignable)
	FOnEndPopup OnEndPopup;
	
	UFUNCTION(BlueprintCallable, Category = "PopupManager")
	void PopupLaunch();

	UFUNCTION(BlueprintCallable, Category = "PopupManager")
	void PopupEnd();


	
};
