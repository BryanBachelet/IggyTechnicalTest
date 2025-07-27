// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "IggyTechnical/Structs/GameID.h"
#include "Logging/LogMacros.h"
#include "IggyTechnicalCharacter.generated.h"

enum class EWorldPlace : uint8;
class UInteractComponent;
class UCharacterQuestComponent;
class UCharacterQuestData;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnLocationChange,EWorldPlace,NewLocation);

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AIggyTechnicalCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* DetectBox;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Quest, meta = (AllowPrivateAccess = "true"))
	UCharacterQuestComponent* QuestComponent;
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	bool IsAtInteractableRange = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInteractComponent* CurrentInteractComponent = nullptr;

	EWorldPlace CurrentLocation ;
	
public:
	AIggyTechnicalCharacter();

	UPROPERTY()
	FOnLocationChange OnLocationChange;
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);



protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();



public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION()
	void OnBoxOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndBoxOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Interact")
	 void OnInteractRangeStart();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Interact")
	void OnInteractRangeOut();
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Interact")
	  void OnInteractEnd();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Quest")
	void AddQuest(UCharacterQuestData* QuestData);

	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Quest")
	void UpdateQuest(UCharacterQuestData* QuestData);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Quest")
	void FinishQuest(FGameID IdQuestFinish);

	// Notify to the character that he has change of location
	void ChangeLocation(EWorldPlace place,FText name);
};

