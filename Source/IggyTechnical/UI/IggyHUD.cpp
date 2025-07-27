#include "IggyHUD.h"

#include "PopupManagerComponent.h"

AIggyHUD::AIggyHUD()
{
	PopupManager = CreateDefaultSubobject<UPopupManagerComponent>(TEXT("PopupManager"));
}

UPopupManagerComponent* AIggyHUD::GetPopupManager()
{
	return PopupManager;
}
