#include "GameID.h"

FGameID::FGameID()
{
	IdType = TypeID::NONE;
	ID = -1;
}

bool FGameID::operator==(const FGameID& b) const
{
	return  ( ID == b.ID && IdType == b.IdType);
}



FString FGameID::ToString() const
{
	return FString::Printf(TEXT("Type %s / Id %i"),*UEnum::GetValueAsName(IdType).ToString(),ID);
}
