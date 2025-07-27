#include "PopupManagerComponent.h"

UPopupManagerComponent::UPopupManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UPopupManagerComponent::AddPopupToQueue(FPopupData PopupData)
{
	PopupQueue.Enqueue(PopupData);
	if(!bIsPopupShow)
	{
		PopupLaunch();
	}
	
	

}

void UPopupManagerComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if(bIsPopupShow)
	{
		PopupTimer += DeltaTime;
		
		if(PopupTimer> CurrentPopupData.DurationPopup-1.1f && !bIsPopupStartToFadeOut)
		{
			OnEndPopup.Broadcast(CurrentPopupData);
			bIsPopupStartToFadeOut = true;
		}
		if(PopupTimer> CurrentPopupData.DurationPopup)
		{
			PopupEnd();
		}
	}
}

void UPopupManagerComponent::PopupLaunch()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow,
									 FString::Printf(TEXT("Popup Launch")));
	PopupQueue.Dequeue(CurrentPopupData);
	PopupTimer =0;
	bIsPopupShow = true;
	OnLaunchPopup.Broadcast(CurrentPopupData);
	bIsPopupStartToFadeOut = false;
}

void UPopupManagerComponent::PopupEnd()
{
	bIsPopupShow = false;
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow,
									 FString::Printf(TEXT("Popup End")));
	if(!PopupQueue.IsEmpty())
	{
		PopupLaunch();
	}
	
}

